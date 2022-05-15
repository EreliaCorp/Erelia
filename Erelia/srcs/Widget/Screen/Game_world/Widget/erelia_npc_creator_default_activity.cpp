#include "widget/screen/game_world/widget/erelia_npc_creator_interface.h"

NPC_creator_interface::Default_activity::Default_activity(NPC_creator_interface* p_owner)
{
	_owner = p_owner;
}

void NPC_creator_interface::Default_activity::execute()
{

}

void NPC_creator_interface::Default_activity::on_transition()
{
	jgl::cout << "Default activity transition" << jgl::endl;
}