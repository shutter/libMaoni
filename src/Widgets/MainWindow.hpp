#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include "../Common/FrameData.hpp"

class RenderWidget;

class MainWindow: public QMainWindow
{
Q_OBJECT

public:
	MainWindow(FrameData& frame_data);

private slots:
	void load_model(QString name = QString());
	void set_background_color(QColor background_color = QColor());
	void set_foreground_color(QColor foreground_color = QColor());
	void snapshot();
	void show_logo(int state);
private:
	FrameData& frame_data;
	RenderWidget* render_widget;
};

#endif /* MAIN_WINDOW_HPP */
