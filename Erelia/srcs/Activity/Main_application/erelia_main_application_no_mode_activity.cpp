#include "erelia.h"

namespace Activity
{
	void No_mode::execute()
	{
		Main_application::Publisher::instance()->notify(Main_application::Event::Initialize);
	}

	void No_mode::on_transition()
	{
		jgl::cout << "Transition to No mode complete" << jgl::endl;
	}
}
