#include "widget/Screen/game_world/Widget/erelia_player_interacter_activity.h"

namespace Player_interact_activity
{
	NPC_creator::NPC_creator(Player_interacter* p_interacter) : Abstract_activity(p_interacter)
	{

	}

	void NPC_creator::execute()
	{

	}

	void NPC_creator::on_transition()
	{
		THROW_INFORMATION("Transition to gamemode NPC_creator");
		_interacter->editor_inventory()->desactivate();
		_interacter->npc_creator_interface()->activate();
	}
}