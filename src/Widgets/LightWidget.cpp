/*
 * LightWidget.cpp
 *
 *  Created on: Jan 30, 2010
 *      Author: stefan
 */

#include "LightWidget.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QMessageBox>
#include <iostream>

LightWidget::LightWidget(FrameData& frame_data, QWidget *parent) :
	QWidget(parent), frame_data(frame_data) {
	QVBoxLayout* mainLayoutV = new QVBoxLayout;

	QHBoxLayout* layoutH = new QHBoxLayout;
	QGroupBox* horizontalGroupBox = new QGroupBox();

	QPushButton* add_button = new QPushButton("add", this);
	connect(add_button, SIGNAL(clicked()), this, SLOT(add_light()));
	layoutH->addWidget(add_button);

	QPushButton* del_button = new QPushButton("del", this);
	connect(del_button, SIGNAL(clicked()), this, SLOT(test()));
	layoutH->addWidget(del_button);

	QPushButton* load_button = new QPushButton("load", this);
	connect(load_button, SIGNAL(clicked()), this, SLOT(test()));
	layoutH->addWidget(load_button);

	horizontalGroupBox->setLayout(layoutH);

	light_chooser = new QComboBox;
	//light_chooser->addItems(AlgorithmNames());
	light_chooser->show();
	mainLayoutV->addWidget(light_chooser);

	mainLayoutV->addWidget(horizontalGroupBox);

	property_browser = new QtTreePropertyBrowser;
	property_browser->show();
	mainLayoutV->addWidget(property_browser);

	setLayout(mainLayoutV);
	setWindowTitle("Light Control");

}

void LightWidget::add_light() {
	std::cout << "add light" << std::endl;

	if (frame_data.lights().size() >= frame_data.max_number_of_lights) {
		QMessageBox::warning(this, "Error", "Maximal Number of Lights reached!");
	} else {
		frame_data.lights().push_back(Light());
	}
}

void LightWidget::test() {
	std::cout << "test" << std::endl;
}
