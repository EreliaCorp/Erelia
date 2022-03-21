#include "erelia.h"

Main_application::Main_application(jgl::Widget* p_parent) : Manager_widget(p_parent)
{
	_initiate_singleton();
	_initiate_network();

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

	// - Example
	//Publisher::instance()->subscribe(Event::Initialize, ACTIVITY_PARAM{  });


	// - Example
	//State_machine::instance()->add_activity(Status::No_mode, new Activity::No_mode());

}

void Main_application::_initiate_network() 
{
	if (UI_configuration_file::server_mode() == true)
		Server_manager::instantiate(this);
	Client_manager::instantiate(this);
	_initiate();
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
