#include "erelia.h"

void Player_info_menu::_on_geometry_change()
{
	jgl::Int space = _area.x / 100;
	jgl::Vector2Int anchor = space * 2;
	jgl::Vector2Int label_size = jgl::Vector2Int(_area.x / 12, _area.y / 18);
	jgl::Vector2Int entry_size = jgl::Vector2Int(_area.x / 3 - label_size.x - space * 2 - anchor.x, label_size.y);

	_username_label->box().set_border_size(label_size.y / 10);
	_username_label->set_geometry(anchor + jgl::Vector2Int(0, label_size.y + space) * 0, label_size);

	_username_entry->box().set_border_size(entry_size.y / 10);
	_username_entry->set_geometry(_username_label->anchor() + jgl::Vector2Int(_username_label->area().x + space, 0), entry_size);

	_password_label->box().set_border_size(label_size.y / 10);
	_password_label->set_geometry(anchor + jgl::Vector2Int(0, label_size.y + space) * 1, label_size);

	_password_entry->box().set_border_size(entry_size.y / 10);
	_password_entry->set_geometry(_password_label->anchor() + jgl::Vector2Int(_password_label->area().x + space, 0), entry_size);
}

void Player_info_menu::_render()
{

}

void Player_info_menu::start()
{
	_username_entry->set_text(Singleton_atlas::configuration_file.player_username());
	_password_entry->set_text(Singleton_atlas::configuration_file.player_password());
}

Player_info_menu::Player_info_menu(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_username_label = new jgl::Text_label("Username : ", this);
	_username_label->label().set_horizontal_align(jgl::Horizontal_alignment::Centred);
	_username_label->label().set_vertical_align(jgl::Vertical_alignment::Centred);
	_username_label->box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_username_label->activate();

	_username_entry = new jgl::Text_entry("", this);
	_username_entry->label().set_horizontal_align(jgl::Horizontal_alignment::Left);
	_username_entry->label().set_vertical_align(jgl::Vertical_alignment::Centred);
	_username_entry->box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_username_entry->activate();

	_password_label = new jgl::Text_label("Password :", this);
	_password_label->label().set_horizontal_align(jgl::Horizontal_alignment::Centred);
	_password_label->label().set_vertical_align(jgl::Vertical_alignment::Centred);
	_password_label->box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_password_label->activate();

	_password_entry = new jgl::Text_entry("", this);
	_password_entry->label().set_hidden(true);
	_password_entry->label().set_horizontal_align(jgl::Horizontal_alignment::Left);
	_password_entry->label().set_vertical_align(jgl::Vertical_alignment::Centred);
	_password_entry->box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_password_entry->activate();
}

jgl::String Player_info_menu::username()
{
	return (_username_entry->label().text());
}

jgl::String Player_info_menu::password()
{
	return (_password_entry->label().text());
}