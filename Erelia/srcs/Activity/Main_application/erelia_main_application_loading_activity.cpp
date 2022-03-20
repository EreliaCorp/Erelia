#include "erelia.h"

namespace Activity
{
	void Loading::execute()
	{
		UI_configuration_file::load(Path_atlas::ui_config_path);
		Translation_atlas::load(UI_configuration_file::language());
		Texture_atlas::instanciate();

		Main_application::Publisher::instance()->notify(Main_application::Event::Loading_completed);
	}

	void Loading::on_transition()
	{
		jgl::cout << "Transition to loading screen complete" << jgl::endl;
	}
}
