#include "../Widgets/RenderWidget.hpp"

#include <GL/ice-t.h>
#include <GL/ice-t_mpi.h>

class IceTWidget: public RenderWidget
{
Q_OBJECT

public:
	IceTWidget(AlgorithmFactory* algorithm_factory_stack,
			MeshLoader* mesh_loader_stack);

	~IceTWidget();

private:
	void draw();

private:
	IceTContext context;
	static IceTWidget* singleton;
	static void static_draw();
};
