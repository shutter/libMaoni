#include <GL/glew.h>
#include "RenderWidget.hpp"
#include <boost/algorithm/string/predicate.hpp>
#include <QFile>
#include <QTextStream>

static void make_light0(Light& l)
{
	l.setIs_light0(true);
	l.setName("LIGHT0 default");
	l.setDiffuse(Color(0.0, 0.0, 0.0, 0.0));
	l.setSpecular(Color(1.0, 1.0, 1.0, 1.0));
}

RenderWidget::RenderWidget(AlgorithmFactory* algorithm_factory_stack,
		MeshLoader* mesh_loader_stack) :
	algorithm_factory_stack(algorithm_factory_stack), mesh_loader_stack(
			mesh_loader_stack)
{
	// create LIGHT0 gl_diffuse(0.0,0.0,0.0,0.0) and gl_specular(1.0,1.0,1.0,1.0)
	lights_.push_back(Light());
	make_light0(lights_[0]);
	tiles_.push_back(Tile());
}

RenderWidget::~RenderWidget()
{
}

void RenderWidget::init()
{
	glewInit();
}

void RenderWidget::draw()
{
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	for (std::size_t i = 0; i < max_number_of_lights; i++)
	{
		if ((lights_.size() - 1) < i)
			glDisable(GL_LIGHT0 + i);
		else
		{
			lights_[i].apply(i);

			if (lights_[i].getShow_bulp())
				drawLight(GL_LIGHT0 + i);
		}
	}

	if (render_algorithm_)
		render_algorithm_->render(model_);
	else
		model_.draw();
}

QString RenderWidget::helpString() const
{
	return "<h2>S i m p l e V i e w e r</h2>"
		"Use the mouse to move the camera around the object. "
		"You can respectively revolve around, zoom and translate with the three mouse buttons. "
		"Left and middle buttons pressed together rotate around the camera view direction axis<br><br>"
		"Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. "
		"Simply press the function key again to restore it. Several keyFrames define a "
		"camera path. Paths are saved when you quit the application and restored at next start.<br><br>"
		"Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, "
		"<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. "
		"See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>"
		"Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). "
		"A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>"
		"A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. "
		"See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>"
		"Press <b>Escape</b> to exit the viewer.";
}

bool RenderWidget::load_model(const char* filename)
{
	if (boost::algorithm::equals(filename, "<teacup>"))
		return model_.set_bezier_mesh(Model::teacup);

	if (boost::algorithm::equals(filename, "<teapot>"))
		return model_.set_bezier_mesh(Model::teapot);

	if (boost::algorithm::equals(filename, "<teaspoon>"))
		return model_.set_bezier_mesh(Model::teaspoon);

	if (boost::algorithm::equals(filename, "<spiral>"))
		return model_.set_bezier_mesh(Model::spiral);

	for (MeshLoader* i = mesh_loader_stack; i; i = i->next)
	{
		if (boost::algorithm::iends_with(filename, i->extension()))
			return i->load_i(model_, filename) && model_.set_bezier_mesh(
					Model::none);
	}

	return false;
}

void RenderWidget::set_render_algorithm(std::string const& name)
{
	for (AlgorithmFactory* i = algorithm_factory_stack; i; i = i->next)
	{
		if (name == i->name())
			render_algorithm_ = i->algorithm();
	}
}

std::size_t RenderWidget::num_algorithms() const
{
	std::size_t num = 0;

	for (AlgorithmFactory* i = algorithm_factory_stack; i; i = i->next)
		++num;

	return num;
}

std::size_t RenderWidget::num_loaders() const
{
	std::size_t num = 0;

	for (MeshLoader* i = mesh_loader_stack; i; i = i->next)
		++num;

	return num;
}

bool RenderWidget::add_light()
{
	if (lights_.size() >= max_number_of_lights)
	{
		return false;
	}
	else
	{
		lights_.push_back(Light());
		return true;
	}
}

bool RenderWidget::remove_light(int i)
{
	if (i == 0)
	{
		return false;
	}
	else
	{
		lights_.erase(lights_.begin() + i);
		return true;
	}
}

unsigned int RenderWidget::get_lights_size()
{
	return lights_.size();
}

Light& RenderWidget::get_light(unsigned int i)
{
	//std::cout << "light pointer: " << &(lights_.at(i)) << std::endl;
	return lights_.at(i);
}

static QDomElement LightToNode(QDomDocument &d, const Light &l)
{
	QDomElement cn = d.createElement("light");

	cn.setAttribute("name", l.getName().c_str());

	cn.setAttribute("pos_x", l.getPosition().x());
	cn.setAttribute("pos_y", l.getPosition().y());
	cn.setAttribute("pos_z", l.getPosition().z());

	cn.setAttribute("ambient_r", l.getAmbient().red());
	cn.setAttribute("ambient_g", l.getAmbient().green());
	cn.setAttribute("ambient_b", l.getAmbient().blue());
	cn.setAttribute("ambient_a", l.getAmbient().alpha());

	cn.setAttribute("diffuse_r", l.getDiffuse().red());
	cn.setAttribute("diffuse_g", l.getDiffuse().green());
	cn.setAttribute("diffuse_b", l.getDiffuse().blue());
	cn.setAttribute("diffuse_a", l.getDiffuse().alpha());

	cn.setAttribute("specular_r", l.getSpecular().red());
	cn.setAttribute("specular_g", l.getSpecular().green());
	cn.setAttribute("specular_b", l.getSpecular().blue());
	cn.setAttribute("specular_a", l.getSpecular().alpha());

	cn.setAttribute("const_att", l.getConst_att());
	cn.setAttribute("lin_att", l.getLin_att());
	cn.setAttribute("quad_att", l.getQuad_att());

	cn.setAttribute("is_spot", l.getIs_spot());

	cn.setAttribute("spot_x", l.getSpot_direction().x());
	cn.setAttribute("spot_y", l.getSpot_direction().y());
	cn.setAttribute("spot_z", l.getSpot_direction().z());

	cn.setAttribute("cut_off", l.getCut_off());
	cn.setAttribute("exponent", l.getExponent());

	cn.setAttribute("is_on", l.getIs_on());
	cn.setAttribute("show_bulp", l.getShow_bulp());

	cn.setAttribute("is_light0", l.getIs_light0());

	return cn;
}

int RenderWidget::export_lights(std::string const& filename)
{
	QDomDocument doc("LightConfig");
	QDomElement root = doc.createElement("lightconfig");
	doc.appendChild(root);

	for (size_t i = 0; i < lights_.size(); i++)
	{
		root.appendChild(LightToNode(doc, lights_.at(i)));
	}

	QFile file(filename.c_str());
	if (!file.open(QIODevice::WriteOnly))
		return -1;

	QTextStream ts(&file);
	ts << doc.toString();

	file.close();
	return 0;
}

int RenderWidget::import_lights(std::string const& filename)
{
	QDomDocument doc("LightConfig");
	QFile file(filename.c_str());
	if (!file.open(QIODevice::ReadOnly))
	{
		return -1;
	}
	if (!doc.setContent(&file))
	{
		file.close();
		return -2;
	}
	file.close();
	QDomElement root = doc.documentElement();
	if (root.tagName() != "lightconfig")
	{
		return -3;
	}
	QDomNode n = root.firstChild();

	lights_.clear();

	while (!n.isNull())
	{
		QDomElement e = n.toElement();
		if (!e.isNull())
		{
			if (e.tagName() == "light")
			{
				Light l;

				l.setName(e.attribute("name", "").toStdString());

				l.setPosition(Vector3(e.attribute("pos_x", "").toFloat(),
						e.attribute("pos_y", "").toFloat(), e.attribute(
								"pos_z", "").toFloat()));

				l.setAmbient(Color(e.attribute("ambient_r", "").toFloat(),
						e.attribute("ambient_g", "").toFloat(), e.attribute(
								"ambient_b", "").toFloat(), e.attribute(
								"ambient_a", "").toFloat()));

				l.setDiffuse(Color(e.attribute("diffuse_r", "").toFloat(),
						e.attribute("diffuse_g", "").toFloat(), e.attribute(
								"diffuse_b", "").toFloat(), e.attribute(
								"diffuse_a", "").toFloat()));

				l.setSpecular(Color(e.attribute("specular_r", "").toFloat(),
						e.attribute("specular_g", "").toFloat(), e.attribute(
								"specular_b", "").toFloat(), e.attribute(
								"specular_a", "").toFloat()));

				l.setConst_att(e.attribute("const_att", "").toFloat());
				l.setLin_att(e.attribute("lin_att", "").toFloat());
				l.setQuad_att(e.attribute("quad_att", "").toFloat());

				l.setIs_spot(e.attribute("is_spot", "").toInt());

				l.setSpot_direction(Vector3(
						e.attribute("spot_x", "").toFloat(), e.attribute(
								"spot_y", "").toFloat(), e.attribute("spot_z",
								"").toFloat()));

				l.setCut_off(e.attribute("cut_off", "").toFloat());
				l.setExponent(e.attribute("exponent", "").toFloat());

				l.setIs_on(e.attribute("is_spot", "").toInt());
				l.setShow_bulp(e.attribute("is_spot", "").toInt());

				l.setIs_light0(e.attribute("is_light0", "").toInt());

				lights_.push_back(l);
			}
		}

		n = n.nextSibling();
	}

	if (lights_.size() == 0)
	{
		lights_.push_back(Light());
		make_light0(lights_[0]);
	}
	return 0;
}

std::vector<Tile> RenderWidget::copy_tiles()
{
	return tiles_;
}

bool RenderWidget::apply_tiles(std::vector<Tile> tiles)
{
	//todo: test if all tiles are defined correctly, in particular the display_ranks
	return true;
}

