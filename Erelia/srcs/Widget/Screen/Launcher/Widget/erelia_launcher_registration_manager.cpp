#include "widget/Screen/Launcher/erelia_launcher_screen.h"
#include "widget/Screen/Launcher/Widget/erelia_launcher_registration_manager.h"
#include "structure/Atlas/erelia_translation_atlas.h"

void Registration_manager::_on_geometry_change()
{
	for (jgl::Size_t i = 0; i < 2; i++)
		_button->boxes()[i].set_border_size(_area.y / 10);
	_button->set_geometry(0, _area);
}

void Registration_manager::_initialize_client()
{

}

void Registration_manager::_initialize_server()
{

}

jgl::Bool Registration_manager::_update()
{
	return (false);
}

Registration_manager::Registration_manager(jgl::Widget* p_parent) : Abstract_manager_widget(p_parent)
{
	_button = new jgl::Button([&](jgl::Data_contener& p_param) {}, this);
	_button->label().set_text(Translation_atlas::string("Register"));
	_button->activate();

	Launcher_screen::Publisher::instance()->subscribe(Launcher_screen::Event::Connection_complete, LAUNCHER_SCREEN_ACTIVITY_PARAM{
			_button->define_function([&](jgl::Data_contener& p_param) {
					jgl::cout << "Registration manager function" << jgl::endl;
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
}