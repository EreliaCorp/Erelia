#include "Widget/Screen/Game_world/WIdget/erelia_entity_renderer.h"
#include "structure/Data/Map/erelia_chunk.h"
#include "structure/Data/Engine/erelia_engine.h"

jgl::Size_t Entity_renderer::nb_render = 0;

void Entity_renderer::_on_geometry_change()
{

}

void Entity_renderer::_render()
{
	jgl::Bool to_print = false;
	for (auto tmp : Engine::instance()->entities())
	{
		if (tmp.second != nullptr)
		{
			if (tmp.first == 1)
			{
				static jgl::Vector2 last_pos[3] = {-1, -1, -1};
				if (last_pos[tmp.first] != tmp.second->pos())
				{
					to_print = true;
					last_pos[tmp.first] = tmp.second->pos();
				}
			}
			jgl::Float depth = _depth + (tmp.second->is_flying() == true ? Chunk::C_LAYER_LENGTH + 1 : Chunk::C_LAYER_LENGTH / 2 + 0.5f);

			if (tmp.second->sprite_sheet() != nullptr)
				tmp.second->sprite_sheet()->draw(tmp.second->sprite(), convert_world_to_screen(tmp.second->pos()), tmp.second->size() * Node::size, depth, 1.0f);
			else
			{
				if (tmp.second->type() == Entity::Type::Player)
					jgl::draw_rectangle_color(jgl::Color::blue(), convert_world_to_screen(tmp.second->pos()), tmp.second->size() * Node::size, depth);
				else if (tmp.second->type() == Entity::Type::NPC)
					jgl::draw_rectangle_color(jgl::Color::green(), convert_world_to_screen(tmp.second->pos()), tmp.second->size() * Node::size, depth);
				else if (tmp.second->type() == Entity::Type::Enemy)
					jgl::draw_rectangle_color(jgl::Color::red(), convert_world_to_screen(tmp.second->pos()), tmp.second->size() * Node::size, depth);
			}

		}
	}
	if (to_print == true)
		jgl::cout << "Render entities" << jgl::endl;
	nb_render++;
}

Entity_renderer::Entity_renderer(jgl::Widget* p_parent) : Overworld_widget(p_parent)
{

}