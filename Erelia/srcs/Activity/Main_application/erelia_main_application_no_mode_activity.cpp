#include "erelia.h"

namespace Activity
{
	void No_mode::execute()
	{
		jgl::cout << "Execute no mode activity" << jgl::endl;
		Main_application::Publisher::instance()->notify(Main_application::Event::Initialize);
	}

	void No_mode::on_transition()
	{
		jgl::cout << "Transition to No mode" << jgl::endl;
	}
}
