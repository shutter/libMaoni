#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include "../Common/FrameData.hpp"

class MainWindow: public QMainWindow
{
Q_OBJECT

public:
	MainWindow(FrameData& frame_data);

private slots:
	void load_model();

	void show_logo(int state);

private:
	FrameData& frame_data;
};

#endif /* MAIN_WINDOW_HPP */
