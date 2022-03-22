#include "erelia.h"

Main_application* Main_application::_instance = nullptr;

Main_application::Main_application(jgl::Widget* p_parent) : Abstract_manager_widget(p_parent)
{
	_instance = this;

	_initiate_network();
	_initiate_singleton();
	_initiate_screen();
	State_machine::instance()->set_state(Status::No_mode);
}

Main_application::~Main_application()
{
	UI_configuration_file::save(Path_atlas::ui_config_path);
}

void Main_application::_initiate_singleton()
{
	Publisher::instanciate();
	State_machine::instanciate();

	Publisher::instance()->subscribe(Main_application::Event::Go_loading, ACTIVITY_PARAM{ "Go to loading"; State_machine::instance()->set_state(Status::Loading); });
	Publisher::instance()->subscribe(Main_application::Event::Go_launcher, ACTIVITY_PARAM{ "Go to connection"; State_machine::instance()->set_state(Status::Launcher); });
	Publisher::instance()->subscribe(Main_application::Event::Go_world, ACTIVITY_PARAM{ "Go to World"; State_machine::instance()->set_state(Status::World_mode); });
	Publisher::instance()->subscribe(Main_application::Event::Go_battle, ACTIVITY_PARAM{ "Go to Battle"; State_machine::instance()->set_state(Status::Battle_mode); });

	State_machine::instance()->add_activity(Status::No_mode, new Main_application::Activity::No_mode());
	State_machine::instance()->add_activity(Status::Loading, new Main_application::Activity::Loading_mode());
	State_machine::instance()->add_activity(Status::Launcher, new Main_application::Activity::Launcher_mode());
	State_machine::instance()->add_activity(Status::World_mode, new Main_application::Activity::World_mode());
	State_machine::instance()->add_activity(Status::Battle_mode, new Main_application::Activity::Battle_mode());
}

void Main_application::_initiate_network() 
{
	UI_configuration_file::load(Path_atlas::ui_config_path);
	if (UI_configuration_file::server_mode() == true)
		Server_manager::instantiate(this);
	Client_manager::instantiate(this);
	_initiate();
}

void Main_application::_initiate_screen()
{
	_screens.push_back(new Loading_screen(this));
	_screens.push_back(new Launcher_screen(this));
	_screens.push_back(new Game_world_screen(this));
	_screens.push_back(new Game_battle_screen(this));
}

void Main_application::transition_to_screen(Screen p_screen)
{
	for (jgl::Size_t i = 0; i < _screens.size(); i++)
	{
		_screens[i]->desactivate();
	}
	if (p_screen != Screen::No_mode)
		_screens[static_cast<jgl::Int>(p_screen)]->activate();
}

void Main_application::_on_geometry_change()
{
	for (jgl::Size_t i = 0; i < _childrens.size(); i++)
	{
		_childrens[i]->set_geometry(0, _area);
	}
}

jgl::Bool Main_application::_update()
{
	State_machine::instance()->update();
	return (false);
}
