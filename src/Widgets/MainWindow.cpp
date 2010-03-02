#include "MainWindow.hpp"

#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(FrameData& frame_data) :
	frame_data(frame_data)
{
	QMenu* file = menuBar()->addMenu("&File");

	QAction* quit = new QAction("&Quit", this);
	file->addAction(quit);

	QMenu* model = menuBar()->addMenu("&Model");

	QAction* cup = new QAction("tea&cup", this);
	model->addAction(cup);

	QAction* pot = new QAction("tea&pot", this);
	model->addAction(pot);

	QAction* spoon = new QAction("tea&spoon", this);
	model->addAction(spoon);

	//! this entry is shown iff there is at least one loader available
	if (MeshLoader::stack)
	{
		model->addSeparator();
		QAction* load = new QAction("&load...", this);
		connect(load, SIGNAL(triggered()), this, SLOT(load_model()));
		model->addAction(load);
	}

	QMenu* help = menuBar()->addMenu("&Help");
	QAction* help_contents = new QAction("&Help Contents", this);
	//connect(help_contents, SIGNAL(triggered()), this, SLOT(show_help()));
	help->addAction(help_contents);
}

void MainWindow::show_help(){

}

void MainWindow::load_model()
{
	QString file = QFileDialog::getOpenFileName(this,
			"Choose the model file to load", "Models/trico.ply",
			MeshLoader::all_filters());

	if (file.isNull())
		return;

	if (!frame_data.load_model(file.toStdString().c_str()))
	{
		QMessageBox::warning(this, "Error", //
				"Could not load file \"" + file + "\"");
	}
}

void MainWindow::show_logo(int state)
{
	std::cout << "show_logo: " << state << std::endl;
}
