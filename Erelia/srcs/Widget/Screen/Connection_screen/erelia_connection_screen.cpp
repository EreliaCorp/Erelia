#include "erelia.h"

Connection_screen* Connection_screen::_instance = nullptr;

void Connection_screen::_on_geometry_change()
{
	jgl::Vector2 unit = _area / jgl::Vector2(86, 64);

	_layout->set_geometry(jgl::Vector2(1, 1) * unit, jgl::Vector2(43, 40) * unit);
	_logo->set_geometry(jgl::Vector2(0.5, 0.5) * unit, jgl::Vector2(42, 20) * unit);
	_username_input.set_geometry(jgl::Vector2(1, 21) * unit, jgl::Vector2(40, 8) * unit);
	_password_input.set_geometry(jgl::Vector2(1, 30) * unit, jgl::Vector2(40, 8) * unit);

	for (jgl::Size_t i = 0; i < 2; i++)
	{
		_register_button->boxes()[i].set_border_size(unit.y / 3);
		_connect_button->boxes()[i].set_border_size(unit.y / 3);
	}

	_register_button->set_geometry(jgl::Vector2(1, 42) * unit, jgl::Vector2(21, 5) * unit);
	_connect_button->set_geometry(jgl::Vector2(23, 42) * unit, jgl::Vector2(21, 5) * unit);


	for (jgl::Size_t i = 0; i < 3; i++)
	{
		_messages_output[i]->set_geometry(jgl::Vector2(45, 1 + 4 * i) * unit, jgl::Vector2(45.5f, 4) * unit);
	}
}

void Connection_screen::_render()
{

}

jgl::Bool Connection_screen::_update()
{
	if (_initiate_state == false && Client_manager::client()->connection()->state() == Connection::State::Accepted)
	{
		_connect_button->define_function([&](jgl::Data_contener& p_param) {Routine::send_connection_request(_username_input.entry->label().text(), _password_input.entry->label().text()); });
		_register_button->define_function([&](jgl::Data_contener& p_param) {Routine::send_registration_request(_username_input.entry->label().text(), _password_input.entry->label().text()); });

		for (jgl::Size_t i = 0; i < 2; i++)
		{
			jgl::Color a = _connect_button->boxes()[i].background_color(), b = _connect_button->boxes()[i].border_color(), c = _connect_button->label().text_color();
			a.a = 1.0f; b.a = 1.0f; c.a = 1.0f;

			_connect_button->boxes()[i].set_color(a, b);
			_register_button->boxes()[i].set_color(a, b);
			_connect_button->label().set_text_color(c);
			_register_button->label().set_text_color(c);
		}

		_initiate_state = true;
		return (true);
	}
	if (_initiate_state == false)
		return (false);
	if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Tab) == jgl::Input_status::Release)
	{
		if (_username_input.entry->is_selected() == true)
		{
			_username_input.entry->unselect();
			_password_input.entry->select();
		}
		else if (_password_input.entry->is_selected() == true)
		{
			_password_input.entry->unselect();
			_username_input.entry->select();
		}
	}
	if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Return) == jgl::Input_status::Release)
	{
		_connect_button->cast();
	}
	return (false);
}

void Connection_screen::set_text(jgl::String p_text_a, jgl::String p_text_b, jgl::String p_text_c)
{
	_messages_output[0]->label().set_text(p_text_a);
	_messages_output[1]->label().set_text(p_text_b);
	_messages_output[2]->label().set_text(p_text_c);
}

void Connection_screen::start()
{
	set_text("");
}

void Connection_screen::_initialize_server()
{
	Server_manager::server()->add_activity(Server_message::Connection_request, SERVER_ACTIVITY {
			Routine::treat_connection_request(p_client, p_msg);}
	);

	Server_manager::server()->add_activity(Server_message::Register_request, SERVER_ACTIVITY {
			Routine::treat_registration_request(p_client, p_msg);}
	);
}

void Connection_screen::_initialize_client()
{
	Client_manager::client()->add_activity(Server_message::Connection_screen_communication, CLIENT_ACTIVITY{
			Routine::treat_connection_message(p_msg);
		});
}

Connection_screen* Connection_screen::instanciate(jgl::Widget* p_parent)
{
	if (_instance == nullptr)
	{
		_instance = new Connection_screen(p_parent);
	}
	return (_instance);
}

Connection_screen::Connection_screen(jgl::Widget* p_parent) : Abstract_screen(p_parent)
{
	_layout = new jgl::Frame(this);
	_layout->box().set_border_size(2);
	_layout->activate();

	_logo = new jgl::Frame(_layout);
	_logo->box().set_image(new jgl::Image(Path_atlas::erelia_logo_path));
	_logo->box().set_border_size(0);
	_logo->activate();

	_username_input = Data_input(Translation_atlas::string("Username"), UI_configuration_file::username(), _layout);
	_password_input = Data_input(Translation_atlas::string("Password"), UI_configuration_file::password(), _layout);
	_password_input.entry->label().set_hidden(true);

	_connect_button = new jgl::Button([&](jgl::Data_contener& p_param) { }, this);
	_connect_button->label().set_text(Translation_atlas::string("Connect"));
	_connect_button->activate();

	_register_button = new jgl::Button([&](jgl::Data_contener& p_param) { }, this);
	_register_button->label().set_text(Translation_atlas::string("Register"));
	_register_button->activate();

	for (jgl::Size_t i = 0; i < 2; i++)
	{
		jgl::Color a = _connect_button->boxes()[i].background_color(), b = _connect_button->boxes()[i].border_color(), c = _connect_button->label().text_color();
		a.a = 0.2f; b.a = 0.2f;

		_connect_button->boxes()[i].set_color(a, b);
		_register_button->boxes()[i].set_color(a, b);
		_connect_button->label().set_text_color(c);
		_register_button->label().set_text_color(c);
	}

	for (jgl::Size_t i = 0; i < 3; i++)
	{
		_messages_output[i] = new jgl::Text_label("", this);
		_messages_output[i]->box().set_color(jgl::Color(0, 0, 0, 0), jgl::Color(0, 0, 0, 0));
		_messages_output[i]->label().set_text_color(jgl::Color::red());
		_messages_output[i]->activate();
	}

	_initiate();
}