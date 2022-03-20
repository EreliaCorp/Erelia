#include "erelia.h"

namespace Activity
{
	void Launcher::execute()
	{
		//jgl::cout << "Execute launcher activity" << jgl::endl;
	}

	void Launcher::on_transition()
	{
		jgl::cout << "Transition to launcher" << jgl::endl;
	}
}
