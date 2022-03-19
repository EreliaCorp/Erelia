#include "erelia.h"

namespace Routine
{
	void receive_battle_start(Message& msg)
	{
		jgl::Uint monster_id;

		msg >> monster_id;

		Main_application::instance()->transition_to_battle();
	}
};