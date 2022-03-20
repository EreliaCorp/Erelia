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
	UI_configuration_file::load(Path_atlas::ui_config_path);
	Translation_atlas::load(UI_configuration_file::language());
	Texture_atlas::instanciate();
	Publisher::instanciate();
	State_machine::instanciate();
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
