#include "widget/Screen/game_world/Widget/erelia_player_interacter_activity.h"

namespace Player_interact_activity
{
	Adventure::Adventure(Player_interacter* p_interacter) : Abstract_activity(p_interacter)
	{

	}

	void Adventure::execute()
	{

	}

	void Adventure::on_transition()
	{
		THROW_INFORMATION("Transition to gamemode Adventure");
		_interacter->editor_inventory()->desactivate();
	}
}