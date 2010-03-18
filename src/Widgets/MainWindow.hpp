#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include "../Common/FrameData.hpp"

class RenderWidget;
class LightWidget;

class MainWindow: public QMainWindow
{
Q_OBJECT

public:
	MainWindow(FrameData& frame_data);

private slots:
	void load_model(QString name = QString());
	void import_lights(QString name = QString());
	void export_lights(QString name = QString());
	void set_background_color(QColor background_color = QColor());
	void set_foreground_color(QColor foreground_color = QColor());
	void snapshot();
//	void quit();
	void show_logo(int state);

private:
	void init_model_menu();
	void init_docks();

private:
	FrameData& frame_data;
	RenderWidget* render_widget;
	LightWidget* light_widget;
};

#endif /* MAIN_WINDOW_HPP */
