#include "widget/screen/game_world/widget/erelia_npc_creator_interface.h"

NPC_creator_interface::Removing_activity::Removing_activity(NPC_creator_interface* p_owner)
{
	_owner = p_owner;
}

void NPC_creator_interface::Removing_activity::execute()
{
	if (jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Left) == jgl::Input_status::Release &&
		_owner->is_pointed() == false)
	{
		_owner->remove_entity();

		NPC_creator_interface::Publisher::instance()->notify(NPC_creator_interface::Event::Remove_complete);
	}
}

void NPC_creator_interface::Removing_activity::on_transition()
{
	jgl::cout << "Removing activity transition" << jgl::endl;
}