#include "widget/screen/game_world/widget/erelia_npc_creator_interface.h"

NPC_creator_interface::Placement_activity::Placement_activity(NPC_creator_interface* p_owner)
{
	_owner = p_owner;
}

void NPC_creator_interface::Placement_activity::execute()
{
	if (jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Left) == jgl::Input_status::Release &&
		_owner->is_pointed() == false)
	{
		_owner->place_entity();

		NPC_creator_interface::Publisher::instance()->notify(NPC_creator_interface::Event::Placement_complete);
	}
}

void NPC_creator_interface::Placement_activity::on_transition()
{
	jgl::cout << "Placement activity transition" << jgl::endl;
}