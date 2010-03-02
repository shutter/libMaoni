#include "MainWindow.hpp"
#include "../Widgets/RenderWidget.hpp"

#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QSignalMapper>

MainWindow::MainWindow(FrameData& frame_data) :
	frame_data(frame_data)
{
	QMenu* file = menuBar()->addMenu("&File");

	QAction* quit = new QAction("&Quit", this);
	file->addAction(quit);

	QMenu* model = menuBar()->addMenu("&Model");
	QSignalMapper* mapper = new QSignalMapper(this);

	QAction* teacup = new QAction("tea&cup", this);
	mapper->setMapping(teacup, "<teacup>");
	connect(teacup, SIGNAL(triggered()), mapper, SLOT(map()));
	model->addAction(teacup);

	QAction* teapot = new QAction("tea&pot", this);
	mapper->setMapping(teapot, "<teapot>");
	connect(teapot, SIGNAL(triggered()), mapper, SLOT(map()));
	model->addAction(teapot);

	QAction* teaspoon = new QAction("tea&spoon", this);
	mapper->setMapping(teaspoon, "<teaspoon>");
	connect(teaspoon, SIGNAL(triggered()), mapper, SLOT(map()));
	model->addAction(teaspoon);

	connect(mapper, SIGNAL(mapped(const QString &)), this,
			SLOT(load_model(QString)));

	//! this entry is shown iff there is at least one loader available
	if (MeshLoader::stack)
	{
		model->addSeparator();
		QAction* load = new QAction("&load...", this);
		connect(load, SIGNAL(triggered()), this, SLOT(load_model()));
		model->addAction(load);
	}

	RenderWidget* render_widget = new RenderWidget(frame_data);
	setCentralWidget(render_widget);

	QMenu* help = menuBar()->addMenu("&Help");
	QAction* help_contents = new QAction("lib&QGLViewer", this);
	connect(help_contents, SIGNAL(triggered()), render_widget, SLOT(help()));
	help->addAction(help_contents);
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

void MainWindow::show_logo(int state)
{
	std::cout << "show_logo: " << state << std::endl;
}
