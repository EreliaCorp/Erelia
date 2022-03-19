#include "erelia.h"

Loading_screen* Loading_screen::_instance = nullptr;

void Loading_screen::_on_geometry_change()
{
	jgl::Vector2 unit = _area / jgl::Vector2(86, 64);

	jgl::Vector2Int label_size = jgl::Vector2(84, 5) * unit;

	for (jgl::Size_t i = 0; i < 3; i++)
	{
		_messages[i]->set_geometry(_area / 2 - label_size / 2 + jgl::Vector2Int(0, label_size.y * 1.1f * i), label_size);
	}
}

void Loading_screen::_render()
{

}

jgl::Bool Loading_screen::_update()
{

	return (false);
}

void Loading_screen::_set_text(jgl::String p_text_a, jgl::String p_text_b, jgl::String p_text_c)
{
	_messages[0]->label().set_text(p_text_a);
	_messages[1]->label().set_text(p_text_b);
	_messages[2]->label().set_text(p_text_c);
}

void Loading_screen::_initialize_server()
{
	Server_manager::server()->add_activity(Server_message::ID_request, SERVER_ACTIVITY{
			Routine::treat_ID_request(p_client, p_msg);
		});
}

void Loading_screen::_initialize_client()
{
	Client_manager::client()->add_activity(Server_message::ID_data, CLIENT_ACTIVITY{
			Routine::receive_player_ID_data(p_msg);
		});
}

Loading_screen* Loading_screen::instanciate(jgl::Widget* p_parent)
{
	if (_instance == nullptr)
	{
		_instance = new Loading_screen(p_parent);
	}
	return (_instance);
}

Loading_screen::Loading_screen(jgl::Widget* p_parent) : Abstract_screen(p_parent)
{
	for (jgl::Size_t i = 0; i < 3; i++)
	{
		_messages[i] = new jgl::Text_label("", this);
		_messages[i]->box().set_color(jgl::Color(0, 0, 0, 0), jgl::Color(0, 0, 0, 0));
		_messages[i]->label().set_text_color(jgl::Color::white());
		_messages[i]->label().set_horizontal_align(jgl::Horizontal_alignment::Centred);
		_messages[i]->label().set_vertical_align(jgl::Vertical_alignment::Centred);
		_messages[i]->activate();
	}

	_initiate();
}

void Loading_screen::start()
{
	_set_text("Connection ...");

	Message msg(Server_message::ID_request);

	Client_manager::client()->send(msg);

	load_monster();
}
