/*
 * libMaoni common viewing framework
 * Copyright (C) 2009, 2010 Daniel Pfeifer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <boost/mpi/environment.hpp>
#include <QApplication>
#include <QSplashScreen>

#include "RenderWidget.hpp"
#include "TilesWidget.hpp"
#include "FrameData.hpp"
#include "../Common/MainWindow.hpp"

#ifdef _MSC_VER
__declspec(dllexport)
#endif
int maoni_main(int argc, char* argv[], //
		RenderAlgorithm* algorithm_stack, MeshLoader* mesh_loader_stack)
{
	boost::mpi::environment env(argc, argv);
	QApplication app(argc, argv);
	Q_INIT_RESOURCE( Resources);

	QPixmap pixmap(":/Maoni/Splashscreen.jpg");
	QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);

	FrameDataIceT framedata(algorithm_stack, mesh_loader_stack);

	RenderWidgetIceT* icet_widget = new RenderWidgetIceT(framedata);

	QWidget* main_window;
	if (framedata.master())
	{
		MainWindow* mw = new MainWindow(framedata, icet_widget);

		TilesWidget* tiles_widget = new TilesWidget(framedata);
		mw->connect(mw, SIGNAL(data_updated()), tiles_widget, SLOT(
				update_browser()));

		mw->add_dock("Tile Config", Qt::LeftDockWidgetArea, //
				tiles_widget);
		main_window = mw;
		splash.show();
	}
	else
	{
		main_window = icet_widget;
	}

	QString window_title("Maoni using IceT Parallel Rendering; Rank %1");
	main_window->setWindowTitle(window_title.arg(framedata.myrank()));

	QTimer::singleShot(1000, main_window, SLOT(show()));
	QTimer::singleShot(1337, &splash, SLOT(close()));

	env.abort(app.exec());
	return 0;
}
