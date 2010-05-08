#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QDialog>

class RenderWidget;
class LightWidget;
//class TilesWidget;
class FrameData;

class MainWindow: public QMainWindow
{
Q_OBJECT

public:
	MainWindow(FrameData& framedata, RenderWidget* render_widget);

	void add_dock(const char* name, Qt::DockWidgetArea area, QWidget *widget);

private slots:
	void about_qt();
	void about_maoni();
	void load_model();
	void import_scene();
	void export_scene();
	void set_background_color();
	void set_foreground_color();
	void snapshot();
//	void quit();
	void show_logo(int state);
	void show_tilesconfig();

private:
	void init_docks();

private:
	FrameData& framedata;
	RenderWidget* render_widget;
	LightWidget* light_widget;
//	TilesWidget* tiles_widget;
	QDialog* tiles_dialog;

	QMenu* dock_menu;
};

#endif /* MAIN_WINDOW_HPP */
