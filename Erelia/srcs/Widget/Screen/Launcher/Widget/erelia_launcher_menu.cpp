#include "widget/Screen/Launcher/Widget/erelia_launcher_menu.h"
#include "structure/Atlas/erelia_translation_atlas.h"
#include "structure/Atlas/erelia_path_atlas.h"
#include "structure/File/erelia_UI_configuration_file.h"

namespace Launcher
{
	Menu::Data_input::Data_input()
	{
		label = nullptr;
		entry = nullptr;
	}

	Menu::Data_input::Data_input(jgl::String p_name, jgl::String p_value, jgl::Widget* p_parent)
	{
		label = new jgl::Text_label(p_name + " :", p_parent);
		label->box().set_color(jgl::Color(0, 0, 0, 0), jgl::Color(0, 0, 0, 0));
		label->box().set_border_size(0);
		label->activate();

		entry = new jgl::Text_entry(p_value, p_parent);
		entry->box().set_color(jgl::Color(255, 255, 255, 80), jgl::Color(255, 255, 255, 80));
		entry->activate();
	}

	void Menu::Data_input::set_geometry(jgl::Vector2Int p_anchor, jgl::Vector2Int p_area)
	{
		jgl::Vector2Int label_size = jgl::Vector2Int(p_area.x / 2, (p_area.y / 3) - p_area.y / 20);
		jgl::Vector2Int entry_size = jgl::Vector2Int(p_area.x, (p_area.y / 3 * 2) - p_area.y / 20);

		jgl::Vector2Int label_pos = jgl::Vector2Int(0, 0);
		jgl::Vector2Int entry_pos = jgl::Vector2Int(0, label_size.y + p_area.y / 10);

		label->set_geometry(p_anchor + label_pos, label_size);
		entry->box().set_border_size(entry_size.y / 10);
		entry->set_geometry(p_anchor + entry_pos, entry_size);
	}

	void Menu::_on_geometry_change()
	{
		_layout->set_geometry(0, _area);

		jgl::Vector2Int logo_size = jgl::Vector2Int(_area.x - _layout->box().border_size() * 4, _area.y / 5 * 2);
		jgl::Vector2Int logo_pos = _layout->box().border_size() * 2;
		_logo->set_geometry(logo_pos, logo_size);

		jgl::Vector2Int input_size = jgl::Vector2Int(logo_size.x - _layout->box().border_size() * 4, (_area.y - logo_size.y - _layout->box().border_size() * 6) / 2);
		_username_input.set_geometry(jgl::Vector2(logo_pos.x + _layout->box().border_size() * 2, logo_pos.y + logo_size.y), input_size);
		_password_input.set_geometry(jgl::Vector2(logo_pos.x + _layout->box().border_size() * 2, logo_pos.y + logo_size.y + input_size.y), input_size);
	}

	void Menu::_render()
	{

	}

	jgl::Bool Menu::_update()
	{
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
			return (true);
		}
		return (false);
	}

	Menu::Menu(jgl::Widget* p_parent) : jgl::Widget(p_parent)
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
	}
}