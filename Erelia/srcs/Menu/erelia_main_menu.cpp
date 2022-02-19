#include "erelia.h"

void Main_menu::_activate_main_menu()
{
	_singleplayer_menu->desactivate();
	_multiplayer_menu->desactivate();
	_host_menu->desactivate();

	_singleplayer_button->activate();
	_multiplayer_button->activate();
	_host_button->activate();
	_setting_button->activate();
	_quit_button->activate();
	_error_label->activate();
}

void Main_menu::_activate_menu(jgl::Widget* p_menu)
{
	p_menu->activate();

	_singleplayer_button->desactivate();
	_multiplayer_button->desactivate();
	_host_button->desactivate();
	_setting_button->desactivate();
	_quit_button->desactivate();
	_error_label->desactivate();
}

void Main_menu::_on_geometry_change()
{
	jgl::Vector2Int subdivision = jgl::Vector2Int(4, 3);
	jgl::Vector2Int minimum_size = jgl::Vector2Int(400, 40);
	jgl::Vector2Int button_size = jgl::Vector2Int(_area.x / subdivision.x < minimum_size.x ? _area.x / subdivision.x : minimum_size.x, _area.y / subdivision.y < minimum_size.y ? _area.y / subdivision.y : minimum_size.y);
	jgl::Vector2Int label_size = jgl::Vector2Int(button_size.x * 2, button_size.y);

	for (jgl::Size_t i = 0; i < 2; i++)
	{
		_singleplayer_button->boxes()[i].set_border_size(button_size.y / 10);
		_multiplayer_button->boxes()[i].set_border_size(button_size.y / 10);
		_host_button->boxes()[i].set_border_size(button_size.y / 10);
	}

	_singleplayer_button->set_geometry(_area / 2 - button_size / 2 + jgl::Vector2Int(0, button_size.y * 1.2f) * -1, button_size);
	_multiplayer_button->set_geometry(_area / 2 - button_size / 2 + jgl::Vector2Int(0, button_size.y * 1.2f) * 0, button_size);
	_host_button->set_geometry(_area / 2 - button_size / 2 + jgl::Vector2Int(0, button_size.y * 1.2f) * 1, button_size);

	float space = (button_size.y * 1.2f - button_size.y) / 2;

	_setting_button->set_geometry(_area / 2 - button_size / 2 + jgl::Vector2Int(0, button_size.y * 1.2f) * 2, jgl::Vector2Int(button_size.x / 2 - space, button_size.y));
	_quit_button->set_geometry(_area / 2 - button_size / 2 + jgl::Vector2Int(button_size.x / 2 + space, 0) + jgl::Vector2Int(0, button_size.y * 1.2f) * 2, jgl::Vector2Int(button_size.x / 2 - space, button_size.y));

	_error_label->set_geometry(_area / 2 - label_size / 2 + jgl::Vector2Int(0, button_size.y * 1.2f) * 3, label_size);

	_calc_text_size();

	_singleplayer_menu->set_geometry(0, _area);
	_multiplayer_menu->set_geometry(0, _area);
	_host_menu->set_geometry(0, _area);
}

void Main_menu::_calc_text_size()
{
	jgl::Size_t text_size = _singleplayer_button->label().text_size();
	if (_multiplayer_button->label().text_size() != 0 && text_size > _multiplayer_button->label().text_size())
		text_size = _multiplayer_button->label().text_size();
	if (_host_button->label().text_size() != 0 && text_size > _host_button->label().text_size())
		text_size = _host_button->label().text_size();
	if (_setting_button->label().text_size() != 0 && text_size > _setting_button->label().text_size())
		text_size = _setting_button->label().text_size();
	if (_quit_button->label().text_size() != 0 && text_size > _quit_button->label().text_size())
		text_size = _quit_button->label().text_size();
	if (_error_label->label().text_size() != 0 && text_size > _error_label->label().text_size())
		text_size = _error_label->label().text_size();

	_singleplayer_button->label().set_text_size(text_size);
	_multiplayer_button->label().set_text_size(text_size);
	_host_button->label().set_text_size(text_size);
	_setting_button->label().set_text_size(text_size);
	_quit_button->label().set_text_size(text_size);
	_error_label->label().set_text_size(text_size);
}

void Main_menu::_render()
{

}

Main_menu::Main_menu(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_singleplayer_menu = new Singleplayer_menu(this);
	_multiplayer_menu = new Multiplayer_menu(this);
	_host_menu = new Host_menu(this);

	_singleplayer_button = new jgl::Button([&](jgl::Data_contener& p_param)
		{
			activate_singleplayer_menu();
		}, this);
	_singleplayer_button->label().set_text("Singleplayer");
	_singleplayer_button->selected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_selected_texture());
	_singleplayer_button->unselected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());

	_multiplayer_button = new jgl::Button([&](jgl::Data_contener& p_param)
		{
			activate_multiplayer_menu();
		}, this);
	_multiplayer_button->label().set_text("Join multiplayer game");
	_multiplayer_button->selected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_selected_texture());
	_multiplayer_button->unselected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());

	_host_button = new jgl::Button([&](jgl::Data_contener& p_param)
		{
			activate_host_menu();
		}, this);
	_host_button->label().set_text("Host game");
	_host_button->selected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_selected_texture());
	_host_button->unselected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());

	_setting_button = new jgl::Button([&](jgl::Data_contener& p_param) {}, this);
	_setting_button->label().set_text("Settings");
	_setting_button->selected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_selected_texture());
	_setting_button->unselected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());

	_quit_button = new jgl::Button([&](jgl::Data_contener& p_param) {jgl::Application::active_application()->quit(); }, this);
	_quit_button->label().set_text("Quit game");
	_quit_button->selected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_selected_texture());
	_quit_button->unselected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());

	_error_label = new jgl::Text_label("", this);
	_error_label->label().set_horizontal_align(jgl::Horizontal_alignment::Centred);
	_error_label->label().set_vertical_align(jgl::Vertical_alignment::Centred);
	_error_label->label().set_text_color(jgl::Color(255, 85, 40, 255));
	_error_label->box().set_background_color(jgl::Color(0, 0, 0, 0));
	_error_label->box().set_border_color(jgl::Color(0, 0, 0, 0));

	_activate_main_menu();
}

void Main_menu::activate_singleplayer_menu()
{
	_activate_menu(_singleplayer_menu);
	_singleplayer_menu->start_selecter_menu();
}

void Main_menu::activate_multiplayer_menu()
{
	_activate_menu(_multiplayer_menu);
	_multiplayer_menu->start_selecter_menu();
}

void Main_menu::activate_host_menu()
{
	_activate_menu(_host_menu);
	_host_menu->start_selecter_menu();
}

void Main_menu::set_error_text(jgl::String p_text)
{
	_error_label->label().set_text_alone(p_text);
	_calc_text_size();
}

void Main_menu::start()
{
	_activate_main_menu();
}