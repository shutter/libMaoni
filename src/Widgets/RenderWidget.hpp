#ifndef RENDER_WIDGET_HPP
#define RENDER_WIDGET_HPP

#include <qglviewer.h>
#include <boost/noncopyable.hpp>

#include "../Common/Light.hpp"
//#include "../Common/Tile.hpp"
#include <Maoni/Model.hpp>
#include <Maoni/detail/Algorithm.hpp>
#include <Maoni/detail/MeshLoader.hpp>

class FrameData;

class RenderWidget: public QGLViewer, private boost::noncopyable
{
Q_OBJECT

public:
	RenderWidget(FrameData& framedata);

	virtual ~RenderWidget();

//	bool load_model(const char* filename);

//	void set_render_algorithm(std::string const& name);

	//! get the amount of render algorithms
//	std::size_t num_algorithms() const;

	//! get the amount of mesh loaders
//	std::size_t num_loaders() const;

//	bool add_light();

//	bool remove_light(int i);

//	unsigned int get_lights_size();

//	Light& get_light(unsigned int i);

//	int export_lights(std::string const& filename);

//	int import_lights(std::string const& filename);

//	std::vector<Tile> copy_tiles();
//
//	bool apply_tiles(std::vector<Tile> tiles);

private:
	void init();
	QString helpString() const;

	void draw_light(int i, Light const& light) const;

protected:
	void draw();

protected:
//	Algorithm::Ptr render_algorithm_;
//	Model model_;

//	static const size_t max_number_of_lights = 8;
//	std::vector<Light> lights_;
//	std::vector<Tile> tiles_;

	FrameData& framedata;

//private:
//	AlgorithmFactory* algorithm_factory_stack;
//	MeshLoader* mesh_loader_stack;
};

#endif /* RENDER_WIDGET_HPP */
