#include "widget/Screen/Launcher/erelia_launcher_screen.h"
#include "widget/Screen/Launcher/Widget/erelia_launcher_connection_manager.h"
#include "structure/Atlas/erelia_translation_atlas.h"
#include "structure/Atlas/erelia_account_atlas.h"
#include "structure/Data/Engine/erelia_engine.h"
#include "widget/Main_application/erelia_main_application.h"

void Connection_manager::_on_geometry_change()
{
	for (jgl::Size_t i = 0; i < 2; i++)
		_button->boxes()[i].set_border_size(_area.y / 10);
	_button->set_geometry(0, _area);
}

void Connection_manager::_initialize_client()
{
	Client_manager::client()->add_activity(Server_message::Connection_accepted, CLIENT_ACTIVITY{
			_treat_connection_approuval(p_msg);
		});
	Client_manager::client()->add_activity(Server_message::Connection_refused, CLIENT_ACTIVITY{
			_treat_connection_rejection(p_msg);
		});
}

void Connection_manager::_initialize_server()
{
	Server_manager::server()->add_activity(Server_message::Connection_request, SERVER_ACTIVITY{
			_treat_connection_request(p_client, p_msg);
		});
}

jgl::Bool Connection_manager::_update()
{
	if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Return) == jgl::Input_status::Release)
	{
		_button->cast();
		return (true);
	}

	return (false);
}

void Connection_manager::_send_connection_request()
{
	static Message msg(Server_message::Connection_request);

	msg.clear();

	msg << Launcher_screen::instance()->username();
	msg << Launcher_screen::instance()->password();

	Client_manager::client()->send(msg);
}

void Connection_manager::_treat_connection_request(Connection* p_client, Message& p_msg)
{
	jgl::String username, password;

	p_msg >> username;
	p_msg >> password;

	Account* tmp_account = Account_atlas::instance()->account(username);

	if (tmp_account != nullptr && tmp_account->password == password && tmp_account->connection == nullptr)
	{
		static Message result(Server_message::Connection_accepted);

		tmp_account->connection = p_client;
		Account_atlas::instance()->activate_account(tmp_account);

		Entity* new_entity = new Entity(Engine::instance()->request_id());

		Engine::instance()->add_entity(new_entity);

		tmp_account->id = new_entity->id();

		result.clear();

		result << tmp_account->id;

		p_client->send(result);
	}
	else
	{
		static Message result(Server_message::Connection_refused);

		result.clear();

		if (tmp_account != nullptr && tmp_account->password == password)
			result << jgl::Int(0);
		else
			result << jgl::Int(1);

		p_client->send(result);
	}
}

void Connection_manager::_treat_connection_approuval(Message& p_msg)
{
	jgl::Long id;

	p_msg >> id;

	THROW_INFORMATION("Initializing player with id [" + jgl::itoa(id) + "]");

	Engine::instance()->initialize_player(id);

	Main_application::Publisher::instance()->notify(Main_application::Event::Go_world);
}

void Connection_manager::_treat_connection_rejection(Message& p_msg)
{
	jgl::Int value;

	p_msg >> value;

	if (value == 0)
		Launcher_screen::instance()->set_text(Translation_atlas::string("Already_connected"));
	else if (value == 1)
		Launcher_screen::instance()->set_text(Translation_atlas::string("Connection_rejected"));
}

Connection_manager::Connection_manager(jgl::Widget* p_parent) : jgl::Updater_widget(p_parent)
{
	_button = new jgl::Button([&](jgl::Data_contener& p_param) {}, this);
	_button->label().set_text(Translation_atlas::string("Connect"));
	_button->activate();

	Launcher_screen::Publisher::instance()->subscribe(Launcher_screen::Event::Connection_complete, LAUNCHER_SCREEN_ACTIVITY_PARAM{
			_button->define_function([&](jgl::Data_contener& p_param) {
					if (Launcher_screen::instance()->username().size() >= 4 && Launcher_screen::instance()->password().size() >= 4)
						_send_connection_request();
				});

			for (jgl::Size_t i = 0; i < 2; i++)
			{
				jgl::Color a = _button->boxes()[i].background_color(), b = _button->boxes()[i].border_color(), c = _button->label().text_color();
				a.a = 1.0f; b.a = 1.0f; c.a = 1.0f;

				_button->boxes()[i].set_color(a, b);
				_button->label().set_text_color(c);
			}
		});


	for (jgl::Size_t i = 0; i < 2; i++)
	{
		jgl::Color a = _button->boxes()[i].background_color(), b = _button->boxes()[i].border_color(), c = _button->label().text_color();
		a.a = 0.2f; b.a = 0.2f;

		_button->boxes()[i].set_color(a, b);
		_button->label().set_text_color(c);
	}

	_initiate();
}