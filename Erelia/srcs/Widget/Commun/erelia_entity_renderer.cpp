#include "erelia.h"

void Entity_renderer::_on_geometry_change()
{

}

void Entity_renderer::_render()
{
	for (auto tmp : Engine::instance()->entities())
	{
		if (tmp.second->sprite_sheet() != nullptr)
			tmp.second->sprite_sheet()->draw(tmp.second->sprite(), convert_world_to_screen(tmp.second->pos()), tmp.second->size() * Node::size, _depth + Chunk::C_LAYER_LENGTH / 2, 1.0f);
		else
			jgl::draw_rectangle_color(jgl::Color::blue(), convert_world_to_screen(tmp.second->pos()), tmp.second->size() * Node::size, _depth + Chunk::C_LAYER_LENGTH / 2);
	}
}

Entity_renderer::Entity_renderer(jgl::Widget* p_parent) : Graphical_widget(p_parent)
{

}