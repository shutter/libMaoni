#include "MainWindow.hpp"
#include "RenderWidget.hpp"
#include "LightWidget.hpp"
#include "AlgorithmWidget.hpp"

#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QSignalMapper>
#include <QColorDialog>
#include <QDockWidget>

MainWindow::MainWindow(FrameData& frame_data) :
	frame_data(frame_data)
{

	render_widget = new RenderWidget(frame_data);
	setCentralWidget(render_widget);

	QMenu* file = menuBar()->addMenu("&File");

	//	render_widget->setFPSIsDisplayed(true);

	QAction* snapshot = new QAction("&Snapshot", this);
	connect(snapshot, SIGNAL(triggered()), this, SLOT(snapshot()));
	file->addAction(snapshot);

	QAction* action = new QAction("&Quit", this);
	connect(action, SIGNAL(triggered()), this, SLOT(close()));
	file->addAction(action);

	init_model_menu();

	QMenu* visual_hints = menuBar()->addMenu("&Visual Hints");
	QAction* fps = new QAction("&FPS", this);
	fps->setCheckable(true);
	connect(fps, SIGNAL(triggered()), render_widget, SLOT(
			toggleFPSIsDisplayed()));
	visual_hints->addAction(fps);

	QAction* grid = new QAction("&grid", this);
	grid->setCheckable(true);
	connect(grid, SIGNAL(triggered()), render_widget, SLOT(toggleGridIsDrawn()));
	visual_hints->addAction(grid);

	QAction* axis = new QAction("&axis", this);
	axis->setCheckable(true);
	connect(axis, SIGNAL(triggered()), render_widget, SLOT(toggleAxisIsDrawn()));
	visual_hints->addAction(axis);

	QAction* background_color = new QAction("&background color", this);
	connect(background_color, SIGNAL(triggered()), this, SLOT(
			set_background_color()));
	visual_hints->addAction(background_color);

	QAction* foreground_color = new QAction("grid &color", this);
	connect(foreground_color, SIGNAL(triggered()), this, SLOT(
			set_foreground_color()));
	visual_hints->addAction(foreground_color);

	init_docks();

	QMenu* help = menuBar()->addMenu("&Help");
	QAction* help_contents = new QAction("lib&QGLViewer", this);
	connect(help_contents, SIGNAL(triggered()), render_widget, SLOT(help()));
	help->addAction(help_contents);
}

void MainWindow::init_model_menu()
{
	QMenu* model = menuBar()->addMenu("&Model");
	QSignalMapper* mapper = new QSignalMapper(this);

	QAction* action = new QAction("tea&cup", this);
	mapper->setMapping(action, "<teacup>");
	connect(action, SIGNAL(triggered()), mapper, SLOT(map()));
	model->addAction(action);

	action = new QAction("tea&pot", this);
	mapper->setMapping(action, "<teapot>");
	connect(action, SIGNAL(triggered()), mapper, SLOT(map()));
	model->addAction(action);

	action = new QAction("tea&spoon", this);
	mapper->setMapping(action, "<teaspoon>");
	connect(action, SIGNAL(triggered()), mapper, SLOT(map()));
	model->addAction(action);

	action = new QAction("lib&QGLViewer spiral", this);
	mapper->setMapping(action, "<spiral>");
	connect(action, SIGNAL(triggered()), mapper, SLOT(map()));
	model->addAction(action);

	connect(mapper, SIGNAL(mapped(const QString &)), this,
			SLOT(load_model(QString)));

	//! this entry is shown iff there is at least one loader available
	if (frame_data.num_loaders() > 0)
	{
		model->addSeparator();
		QAction* load = new QAction("&load...", this);
		connect(load, SIGNAL(triggered()), this, SLOT(load_model()));
		model->addAction(load);
	}
}

void MainWindow::init_docks()
{
	QMenu* menu = menuBar()->addMenu("&Window");

	QDockWidget *dock = new QDockWidget("Stefan's LightWidget", this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	QAction* action = new QAction("Stefan's &LightWidget", this);
	connect(action, SIGNAL(triggered()), dock, SLOT(show()));
	menu->addAction(action);

	dock->setWidget(new LightWidget(frame_data));
	addDockWidget(Qt::LeftDockWidgetArea, dock);

	if (frame_data.num_algorithms() > 0)
	{
		dock = new QDockWidget("Daniel's AlgorithmWidget", this);
		dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

		action = new QAction("Daniel's &AlgorithmWidget", this);
		connect(action, SIGNAL(triggered()), dock, SLOT(show()));
		menu->addAction(action);

		dock->setWidget(new AlgorithmWidget(frame_data));
		addDockWidget(Qt::RightDockWidgetArea, dock);
	}
}

void MainWindow::load_model(QString filename)
{
	if (filename.isNull())
	{
		filename = QFileDialog::getOpenFileName(this,
				"Choose the model file to load", "Models/trico.ply",
				MeshLoader::all_filters());
	}

	if (filename.isNull())
		return;

	if (!frame_data.load_model(filename.toStdString().c_str()))
	{
		QMessageBox::warning(this, "Error", //
				"Could not load file \"" + filename + "\"");
	}
}

void MainWindow::set_background_color(QColor background_color)
{
	background_color = QColorDialog::getColor(Qt::black, this,
			"Choose the background color", 0);

	render_widget->setBackgroundColor(background_color);
}

void MainWindow::set_foreground_color(QColor foreground_color)
{
	foreground_color = QColorDialog::getColor(Qt::white, this,
			"Choose the grid color", 0);
	render_widget->setForegroundColor(foreground_color);
}

void MainWindow::snapshot()
{
	render_widget->saveSnapshot(false, false);
}

void MainWindow::show_logo(int state)
{
	std::cout << "show_logo: " << state << std::endl;
}
