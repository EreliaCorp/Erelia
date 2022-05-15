#include "widget/Screen/game_world/widget/erelia_npc_creator_interface.h"

void NPC_creator_interface::Entity_renderer::_on_geometry_change()
{
	_box.set_geometry(_anchor, _area, _depth);
}

void NPC_creator_interface::Entity_renderer::_render()
{
	_box.render();
	if ((*_to_render) != nullptr)
		(*_to_render)->render(_anchor + _box.border_size(), _area - _box.border_size() * 2, _depth + 1);
}

NPC_creator_interface::Entity_renderer::Entity_renderer(Entity** p_entity, jgl::Widget* p_parent) : jgl::Widget(p_parent),
	_to_render(p_entity),
	_box(this)
{
	_box.set_border_color(jgl::Color(100, 100, 100));
	_box.set_background_color(jgl::Color(150, 150, 150));
}