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

#include <QApplication>
#include <QSplashScreen>
#include "Common/FrameData.hpp"
#include "Common/MainWindow.hpp"
#include "Common/RenderWidget.hpp"

#ifdef _MSC_VER
__declspec(dllexport)
#endif
int maoni_main(int argc, char* argv[], //
		RenderAlgorithm* algorithm_stack, MeshLoader* mesh_loader_stack)
{
	QApplication app(argc, argv);
	Q_INIT_RESOURCE(Resources);

	QPixmap pixmap(":/Maoni/Splashscreen.jpg");
	QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
	splash.show();
	splash.showMessage("Loading Widgets...");

	FrameData framedata(algorithm_stack, mesh_loader_stack);

	MainWindow main_window(framedata, new RenderWidget(framedata));
	main_window.setWindowTitle("Maoni");

	QTimer::singleShot(1000, &main_window, SLOT(show()));
	QTimer::singleShot(1337, &splash, SLOT(close()));

	return app.exec();
}
