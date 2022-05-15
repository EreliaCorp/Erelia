#include "widget/screen/game_world/widget/erelia_npc_creator_interface.h"

NPC_creator_interface::Selection_activity::Selection_activity(NPC_creator_interface* p_owner)
{
	_owner = p_owner;
}

void NPC_creator_interface::Selection_activity::execute()
{
	if (jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Left) == jgl::Input_status::Release && 
		_owner->is_pointed() == false)
	{
		_owner->select_entity();

		if (_owner->entity() != nullptr)
			NPC_creator_interface::Publisher::instance()->notify(NPC_creator_interface::Event::Selection_complete);
	}
}

void NPC_creator_interface::Selection_activity::on_transition()
{
	jgl::cout << "Selection activity transition" << jgl::endl;
}