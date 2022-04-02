#include "widget/Screen/Game_world/widget/erelia_wrap_renderer.h"
#include "structure/data/engine/erelia_engine.h"

void Wrap_renderer::_on_geometry_change()
{

}

void Wrap_renderer::_render()
{
	auto tmp_wrap = Engine::instance()->wraps();

	for (auto tmp : tmp_wrap)
	{
		jgl::draw_rectangle_color(jgl::Color(255, 255, 255, 120), convert_world_to_screen(tmp.second), Node::size, Chunk::C_LAYER_LENGTH + 2);
	}
}


Wrap_renderer::Wrap_renderer(jgl::Widget* p_parent) : Overworld_widget(p_parent)
{

}
