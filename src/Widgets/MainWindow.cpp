#include "MainWindow.hpp"
#include "RenderWidget.hpp"
#include "LightWidget.hpp"
#include "AlgorithmWidget.hpp"
//#include "TilesWidget.hpp"
#include "../Common/FrameData.hpp"
#include "../Common/ImportExport.hpp"

#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QSignalMapper>
#include <QColorDialog>
#include <QDockWidget>
#include <QDialog>

MainWindow::MainWindow(FrameData& framedata, RenderWidget* render_widget) :
	framedata(framedata), render_widget(render_widget)
{
	setCentralWidget(render_widget);

#include "../Images/stanford-bunny.xpm"
	setWindowIcon(QPixmap(stanford_bunny_xpm));

	QMenu* file = menuBar()->addMenu("&File");

	QAction* import_lights = new QAction("&Import Lights", this);
	connect(import_lights, SIGNAL(triggered()), this, SLOT(import_lights()));
	file->addAction(import_lights);

	QAction* export_lights = new QAction("&Export Lights", this);
	connect(export_lights, SIGNAL(triggered()), this, SLOT(export_lights()));
	file->addAction(export_lights);

	file->addSeparator();

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

	action = new QAction("libQGLViewer &Help", this);
	connect(action, SIGNAL(triggered()), render_widget, SLOT(help()));
	help->addAction(action);

	help->addSeparator();

	action = new QAction("about lib&Maoni", this);
	connect(action, SIGNAL(triggered()), this, SLOT(about_maoni()));
	help->addAction(action);

	action = new QAction("about libQGL&Viewer", this);
	connect(action, SIGNAL(triggered()), render_widget, SLOT(aboutQGLViewer()));
	help->addAction(action);

	action = new QAction("about &Qt", this);
	connect(action, SIGNAL(triggered()), this, SLOT(about_qt()));
	help->addAction(action);
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
	if (framedata.num_loaders() > 0)
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

	light_widget = new LightWidget(framedata);
	dock->setWidget(light_widget);
	addDockWidget(Qt::LeftDockWidgetArea, dock);

	if (framedata.num_algorithms() > 0)
	{
		dock = new QDockWidget("Daniel's AlgorithmWidget", this);
		dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

		action = new QAction("Daniel's &AlgorithmWidget", this);
		connect(action, SIGNAL(triggered()), dock, SLOT(show()));
		menu->addAction(action);

		dock->setWidget(new AlgorithmWidget(framedata));
		addDockWidget(Qt::RightDockWidgetArea, dock);
	}

	//	tiles_widget = new TilesWidget(*render_widget);
	//	action = new QAction("&Tiles Config", this);
	//	connect(action, SIGNAL(triggered()), this, SLOT(show_tilesconfig()));
	//	menu->addAction(action);
}

void MainWindow::about_qt()
{
	QMessageBox::aboutQt(this);
}

void MainWindow::about_maoni()
{
	QMessageBox::about(
			this,
			"About libMaoni",
			"A versatile 3D viewer based on OpenGL and Qt.<br>"
				"Copyright 2009-2010 Stefan Hutter, Daniel Pfeifer.<br>"
				"<a href=\"http://github.com/purpleKarrot/libMaoni\">http://github.com/purpleKarrot/libMaoni</a>");
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

	if (!framedata.load_model(filename.toStdString().c_str()))
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

void MainWindow::import_lights(QString filename)
{
	if (filename.isNull())
	{
		filename = QFileDialog::getOpenFileName(this,
				"Choose a light config file to load", "lights.xml", tr(
						"XML Files (*.xml)"));
	}

	if (filename.isNull())
		return;

	int status = ::import_lights(filename.toStdString().c_str(), framedata);
	if (status < 0)
	{
		QMessageBox::warning(this, "Error", //
				status + ": Could not import from file \"" + filename + "\"");
	}
	else
	{
		light_widget->update_browser();
	}
}

void MainWindow::export_lights(QString filename)
{
	if (filename.isNull())
	{
		filename = QFileDialog::getSaveFileName(this,
				"Choose a filename to export the lights config to",
				"lights.xml", tr("XML Files (*.xml)"));
	}

	if (filename.isNull())
		return;

	if (::export_lights(filename.toStdString().c_str(), framedata) < 0)
	{
		QMessageBox::warning(this, "Error", //
				"Could not export to file \"" + filename + "\"");
	}
}

void MainWindow::show_tilesconfig()
{
	if (!tiles_dialog)
	{
		tiles_dialog = new QDialog(this);
		connect(tiles_dialog, SIGNAL(accepted()), this, SLOT(show_logo(1)));
		connect(tiles_dialog, SIGNAL(finished()), this, SLOT(show_logo(2)));
		connect(tiles_dialog, SIGNAL(rejected()), this, SLOT(show_logo(3)));
	}
	tiles_dialog->show();
	//    tiles_dialog->raise();
	//    tiles_dialog->activateWindow();

}
