/*
 * RenderControlWidget.cpp
 *
 *  Created on: Dec 5, 2009
 *      Author: stefan
 */

#include "RenderControlWidget.hpp"
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>

RenderControlWidget::RenderControlWidget(FrameData& frame_data, QWidget *parent) :
	QWidget(parent), frame_data(frame_data)
{
	QVBoxLayout* layout = new QVBoxLayout;

	QPushButton* load_button = new QPushButton("load model", this);
	connect(load_button, SIGNAL(clicked ()), this, SLOT(load_model()));
	layout->addWidget(load_button);

	QCheckBox* logo_box = new QCheckBox(this);
	logo_box->setText("show logo");
	connect(logo_box, SIGNAL(stateChanged(int)), this, SLOT(show_logo(int)));
	layout->addWidget(logo_box);

	setLayout(layout);
	setWindowTitle("Render Control");
}

void RenderControlWidget::load_model()
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

void RenderControlWidget::show_logo(int state)
{
	std::cout << "show_logo: " << state << std::endl;
}
