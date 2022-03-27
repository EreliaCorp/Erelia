#include "widget/Screen/Launcher/erelia_launcher_screen.h"
#include "widget/Screen/Launcher/Widget/erelia_launcher_registration_manager.h"
#include "structure/Atlas/erelia_translation_atlas.h"
#include "structure/Atlas/erelia_account_atlas.h"

void Registration_manager::_on_geometry_change()
{
	for (jgl::Size_t i = 0; i < 2; i++)
		_button->boxes()[i].set_border_size(_area.y / 10);
	_button->set_geometry(0, _area);
}

void Registration_manager::_initialize_client()
{
	Client_manager::client()->add_activity(Server_message::Registration_accepted, CLIENT_ACTIVITY{
			_treat_registration_approuval(p_msg);
		});
	Client_manager::client()->add_activity(Server_message::Registration_refused, CLIENT_ACTIVITY{
			_treat_registration_rejection(p_msg);
		});
}

void Registration_manager::_initialize_server()
{
	Server_manager::server()->add_activity(Server_message::Registration_request, SERVER_ACTIVITY{
			_treat_registration_request(p_client, p_msg);
		});
}

jgl::Bool Registration_manager::_update()
{
	return (false);
}

void Registration_manager::_send_registration_request()
{
	static Message msg(Server_message::Registration_request);

	msg.clear();

	msg << Launcher_screen::instance()->username();
	msg << Launcher_screen::instance()->password();

	Client_manager::client()->send(msg);
}

void Registration_manager::_treat_registration_request(Connection* p_client, Message& p_msg)
{
	jgl::String username, password;

	p_msg >> username;
	p_msg >> password;

	Account* tmp_account = Account_atlas::instance()->account(username);

	if (tmp_account == nullptr)
	{
		Account_atlas::instance()->add_account(username, password);

		static Message result(Server_message::Registration_accepted);

		result.clear();

		p_client->send(result);
	}
	else
	{
		static Message result(Server_message::Registration_refused);

		result.clear();

		p_client->send(result);
	}
}

void Registration_manager::_treat_registration_approuval(Message& p_msg)
{
	Launcher_screen::instance()->set_text(Translation_atlas::string("Registration_accepted"));
}

void Registration_manager::_treat_registration_rejection(Message& p_msg)
{
	Launcher_screen::instance()->set_text(Translation_atlas::string("Registration_rejected"));
}

Registration_manager::Registration_manager(jgl::Widget* p_parent) : jgl::Updater_widget(p_parent)
{
	_button = new jgl::Button([&](jgl::Data_contener& p_param) {}, this);
	_button->label().set_text(Translation_atlas::string("Register"));
	_button->activate();

	Launcher_screen::Publisher::instance()->subscribe(Launcher_screen::Event::Connection_complete, LAUNCHER_SCREEN_ACTIVITY_PARAM{
			_button->define_function([&](jgl::Data_contener& p_param) {
					if (Launcher_screen::instance()->username().size() >= 4 && Launcher_screen::instance()->password().size() >= 4)
						_send_registration_request();
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