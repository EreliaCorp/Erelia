#include "erelia.h"

Main_application::Main_application(jgl::Widget* p_parent) : Manager_widget(p_parent)
{
	_initiate_singleton();
	_initiate_network();
}

Main_application::~Main_application()
{
	UI_configuration_file::save(Path_atlas::ui_config_path);
}

void Main_application::_initiate_singleton()
{
	Publisher::instanciate();
	State_machine::instanciate();

	Event_subscriber* tmp_subscriber = new Event_subscriber();

	Publisher::instance()->subscribe(Event::Initialize, tmp_subscriber);
	Publisher::instance()->subscribe(Event::Start_loading, tmp_subscriber);
	Publisher::instance()->subscribe(Event::Loading_completed, tmp_subscriber);
	Publisher::instance()->subscribe(Event::Transition_launcher, tmp_subscriber);

	_subscriber_array.push_back(tmp_subscriber);

	State_machine::instance()->add_activity(Status::No_mode, new Activity::No_mode());
	State_machine::instance()->add_activity(Status::Loading, new Activity::Loading());
	State_machine::instance()->add_activity(Status::Launcher, new Activity::Launcher());

	State_machine::instance()->set_state(Status::No_mode);
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
