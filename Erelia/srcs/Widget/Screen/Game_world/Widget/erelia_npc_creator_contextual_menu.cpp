#include "widget/Screen/game_world/widget/erelia_npc_creator_interface.h"

void NPC_creator_interface::Contextual_menu::_on_geometry_change()
{
	jgl::Vector2Int space = _area.y / 15;
	jgl::Vector2Int button_size = jgl::Vector2Int(_area.x, (_area.y - space.y * 3) / 4);

	jgl::Vector2Int pos = 0;
	for (jgl::Size_t i = 0; i < 4; i++)
	{
		_buttons[i]->set_geometry(pos, button_size);
		pos.y += button_size.y + space.y;
	}
}

void NPC_creator_interface::Contextual_menu::_render()
{

}

NPC_creator_interface::Contextual_menu::Contextual_menu(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	for (jgl::Size_t i = 0; i < 4; i++)
	{
		jgl::Data_contener param;

		param << i;
		_buttons[i] = new jgl::Button([&](jgl::Data_contener& p_param) {
				jgl::Size_t it;
				p_param >> it;
				jgl::cout << "Button ID [" << it << "]" << jgl::endl;
				p_param.reset();
			}, param, this);
		_buttons[i]->set_depth(_depth + 2);
	}
}

jgl::Button* NPC_creator_interface::Contextual_menu::button(jgl::Size_t p_index)
{
	if (p_index < 4)
		return (_buttons[p_index]);
	return (nullptr);
}