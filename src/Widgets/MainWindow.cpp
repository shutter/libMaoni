#include "MainWindow.hpp"
#include "RenderWidget.hpp"
#include "LightWidget.hpp"
#include "AlgorithmWidget.hpp"
#include "AnimationWidget.hpp"
#include "TextOutput.hpp"
#include "../Common/FrameData.hpp"

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
	setWindowIcon( QPixmap(stanford_bunny_xpm));

	QAction* action;
	QMenu* file = menuBar()->addMenu("&File");

	//! this entry is shown iff there is at least one loader available
	if (framedata.num_loaders() > 0)
	{
		action = new QAction("Load &Model...", this);
		connect(action, SIGNAL(triggered()), this, SLOT(load_model()));
		file->addAction(action);
		file->addSeparator();
	}

	action = new QAction("&Import Scene", this);
	connect(action, SIGNAL(triggered()), this, SLOT(import_scene()));
	file->addAction(action);

	action = new QAction("&Export Scene", this);
	connect(action, SIGNAL(triggered()), this, SLOT(export_scene()));
	file->addAction(action);

	file->addSeparator();

	action = new QAction("&Snapshot", this);
	connect(action, SIGNAL(triggered()), this, SLOT(snapshot()));
	file->addAction(action);

	action = new QAction("&Quit", this);
	connect(action, SIGNAL(triggered()), this, SLOT(close()));
	file->addAction(action);

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

	visual_hints->addSeparator();

	QAction* logo_path = new QAction("&set logo path", this);
	connect(logo_path, SIGNAL(triggered()), render_widget, SLOT(
		set_logo_path()));
	visual_hints->addAction(logo_path);

	QAction* logo = new QAction("&render logo", this);
	logo->setCheckable(true);
	connect(logo, SIGNAL(triggered(bool)), render_widget, SLOT(
		set_logo(bool)));
	logo->setChecked(render_widget->logo_is_enabled());
	visual_hints->addAction(logo);

	dock_menu = menuBar()->addMenu("&Window");
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

void MainWindow::add_dock(const char* name, Qt::DockWidgetArea area,
	QWidget *widget, bool visible)
{
	QDockWidget *dock = new QDockWidget(name, this);
	dock->setAllowedAreas(Qt::AllDockWidgetAreas);

	dock_menu->addAction(dock->toggleViewAction());

	dock->setWidget(widget);
	addDockWidget(area, dock);
	dock->setVisible(visible);
}

void MainWindow::init_docks()
{
	LightWidget* light_widget = new LightWidget(framedata);
	connect(this, SIGNAL(data_updated()), light_widget, SLOT(update_browser()));
	add_dock("LightWidget", Qt::LeftDockWidgetArea, light_widget);

	if (framedata.num_algorithms() > 0)
	{
		AlgorithmWidget* algo_widget = new AlgorithmWidget(framedata);
		connect(this, SIGNAL(data_updated()), algo_widget, SLOT(update_browser()));
		add_dock("AlgorithmWidget", Qt::RightDockWidgetArea,
			algo_widget);
	}

	AnimationWidget* animation_widget = new AnimationWidget(render_widget);
		add_dock("AnimationWidget", Qt::LeftDockWidgetArea, animation_widget, false);

//	add_dock("Output", Qt::BottomDockWidgetArea, new TextOutput);
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

class append_filter
{
public:
	append_filter(QString& filter) :
		filter(filter)
	{
		filter = "All files (*.*)";
	}

	void operator()(MeshLoader* loader)
	{
		filter += QString(";;%1 (*.%2)").arg(loader->name()).arg(
			loader->extension());
	}

private:
	QString& filter;
};

void MainWindow::load_model()
{
	QString filter;
	framedata.for_each_loader(append_filter(filter));
	QString filename = QFileDialog::getOpenFileName(this,
		"Choose the model file to load", "Models/trico.ply", filter);

	if (filename.isNull())
		return;

	try
	{
		framedata.load_model(filename.toStdString().c_str());
	}
	catch (std::exception& e)
	{
		QMessageBox::warning(this, "Error", //
			"Exception caught while loading \"" + filename + "\":\n" + e.what());
	}
	catch (...)
	{
		QMessageBox::warning(this, "Error", //
			"Unknown exception caught while loading \"" + filename + "\".");
	}
}

void MainWindow::set_background_color()
{
	render_widget->setBackgroundColor(QColorDialog::getColor(Qt::black, this,
		"Choose the background color", 0));
}

void MainWindow::set_foreground_color()
{
	render_widget->setForegroundColor(QColorDialog::getColor(Qt::white, this,
		"Choose the grid color", 0));
}

void MainWindow::snapshot()
{
	render_widget->saveSnapshot(false, false);
}

void MainWindow::import_scene()
{
	QString filename = QFileDialog::getOpenFileName(this,
		"Choose a light config file to load", "maoni.xml", tr(
			"XML Files (*.xml)"));

	if (filename.isNull())
		return;

	try
	{
		framedata.import_scene(filename.toStdString().c_str());
	}
	catch (std::exception&e)
	{
		QMessageBox::warning(this, "Error", e.what());
	}

	emit data_updated();
}

void MainWindow::export_scene()
{
	QString filename = QFileDialog::getSaveFileName(this,
		"Choose a filename to export the lights config to", "maoni.xml", tr(
			"XML Files (*.xml)"));

	if (filename.isNull())
		return;

	try
	{
		framedata.export_scene(filename.toStdString().c_str());
	}
	catch (std::exception&e)
	{
		QMessageBox::warning(this, "Error", e.what());
	}
}
