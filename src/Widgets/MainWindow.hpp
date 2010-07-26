#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QDialog>

class RenderWidget;
class FrameData;
class LightWidget;
class AlgorithmWidget;

class MainWindow: public QMainWindow
{
Q_OBJECT

public:
	MainWindow(FrameData& framedata, RenderWidget* render_widget);

	void add_dock(const char* name, Qt::DockWidgetArea area, QWidget *widget,
			bool visible = true);

private slots:
	void about_qt();
	void about_maoni();
	void load_model();
	void import_scene();
	void export_scene();
	void set_background_color();
	void set_foreground_color();
	void snapshot();

signals:
void data_updated();

private:
	void init_docks();

private:
	FrameData& framedata;
	RenderWidget* render_widget;
	AlgorithmWidget* algo_widget;
	LightWidget* light_widget;
	QMenu* dock_menu;
};

#endif /* MAIN_WINDOW_HPP */
