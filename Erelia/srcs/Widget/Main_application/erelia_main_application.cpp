#include "erelia.h"
#include "Widget/commun/erelia_console_manager.h"
#include "Structure/Data/Engine/erelia_engine.h"

Main_application* Main_application::_instance = nullptr;

void Main_application::_initialize_client()
{

}

void Main_application::_initialize_server()
{

}

Main_application::Main_application(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_instance = this;
	_active_screen = nullptr;

	_initiate_singleton();
	_initiate_network();
	_initiate_screen();

	Debug_screen::instanciate(this);
	Debug_screen::instance()->set_depth(1000);
	Debug_screen::instance()->desactivate();

	State_machine::instance()->set_state(Status::No_mode);
}

Main_application::~Main_application()
{
	UI_configuration_file::save(Path_atlas::ui_config_path);
	if (Server_manager::instance() != nullptr)
		Engine::instance()->save();
	if (Account_atlas::instance() != nullptr)
		Account_atlas::instance()->save();
}

void Main_application::_initiate_singleton()
{
	UI_configuration_file::load(Path_atlas::ui_config_path);

	Translation_atlas::load(UI_configuration_file::language());

	Texture_atlas::instanciate();
	Texture_atlas::instance()->load();

	Publisher::instanciate();
	State_machine::instanciate();

	Publisher::instance()->subscribe(Main_application::Event::Go_loading, MAIN_APPLICATION_ACTIVITY_PARAM{ "Go to loading"; State_machine::instance()->set_state(Status::Loading); });
	Publisher::instance()->subscribe(Main_application::Event::Go_launcher, MAIN_APPLICATION_ACTIVITY_PARAM{ "Go to connection"; State_machine::instance()->set_state(Status::Launcher); });
	Publisher::instance()->subscribe(Main_application::Event::Go_world, MAIN_APPLICATION_ACTIVITY_PARAM{ "Go to World"; State_machine::instance()->set_state(Status::World_mode); });

	State_machine::instance()->add_activity(Status::No_mode, new Main_application::Activity::No_mode());
	State_machine::instance()->add_activity(Status::Loading, new Main_application::Activity::Loading_mode());
	State_machine::instance()->add_activity(Status::Launcher, new Main_application::Activity::Launcher_mode());
	State_machine::instance()->add_activity(Status::World_mode, new Main_application::Activity::World_mode());
}

void Main_application::_initiate_network() 
{
	if (UI_configuration_file::server_mode() == true)
		Server_manager::instantiate(this);
	Client_manager::instantiate(this);
	_initiate();
}

void Main_application::_initiate_screen()
{
	_screens.push_back(Loading_screen::instanciate(this));
	_screens.push_back(Launcher_screen::instanciate(this));
	_screens.push_back(Game_world_screen::instanciate(this));

	for (jgl::Size_t i = 0; i < _screens.size(); i++)
	{
		_screens[i]->desactivate();
	}

	Console_manager::instanciate(this);
	Console_manager::instance()->set_depth(1000);
	Console_manager::instance()->desactivate();
}

void Main_application::transition_to_screen(Screen p_screen)
{
	if (_active_screen != nullptr)
		_active_screen->unfocus();
	
	for (jgl::Size_t i = 0; i < _screens.size(); i++)
	{
		_screens[i]->desactivate();
	}

	_active_screen = (p_screen != Screen::No_mode ? _screens[static_cast<jgl::Int>(p_screen)] : nullptr);

	if (_active_screen != nullptr)
	{
		_active_screen->activate();
		_active_screen->focus();
	}
}

void Main_application::_render()
{

}

void Main_application::_on_geometry_change()
{
	Debug_screen::instance()->set_geometry(0, _area);
	Console_manager::instance()->set_geometry(0, _area);
	for (jgl::Size_t i = 0; i < _screens.size(); i++)
	{
		_screens[i]->set_geometry(0, _area);
	}
}

jgl::Bool Main_application::_update()
{
	if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::F3) == jgl::Input_status::Release)
	{
		Debug_screen::instance()->set_active(!(Debug_screen::instance()->active()));
	}
	State_machine::instance()->update();
	return (false);
}
