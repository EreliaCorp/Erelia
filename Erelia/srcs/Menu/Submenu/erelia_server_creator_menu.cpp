#include "erelia.h"

void Server_creator_menu::_on_geometry_change()
{
	jgl::Int space = _area.x / 50;
	jgl::Vector2Int label_size = jgl::Vector2Int(_area.x / 12, _area.y / 18);
	jgl::Vector2Int button_size = jgl::Vector2Int(_area.x / 6, _area.y / 18);
	jgl::Vector2Int entry_size = jgl::Vector2Int(_area.x - space - (space * 3) * 4 - label_size.x, label_size.y);
	jgl::Vector2Int anchor = (space * 3) * 2;

	_server_name_label->box().set_border_size(label_size.y / 10);
	_server_name_label->set_geometry(anchor + jgl::Vector2Int(0, label_size.y + space) * 0, label_size);

	_server_name_entry->box().set_border_size(entry_size.y / 10);
	_server_name_entry->set_geometry(_server_name_label->anchor() + jgl::Vector2Int(_server_name_label->area().x + space, 0), entry_size);

	_server_ip_label->box().set_border_size(label_size.y / 10);
	_server_ip_label->set_geometry(anchor + jgl::Vector2Int(0, label_size.y + space) * 1, label_size);

	_server_ip_entry->box().set_border_size(entry_size.y / 10);
	_server_ip_entry->set_geometry(_server_ip_label->anchor() + jgl::Vector2Int(_server_ip_label->area().x + space, 0), entry_size);

	_cancel_server_creation_button->selected_box().set_border_size(button_size.y / 10);
	_cancel_server_creation_button->unselected_box().set_border_size(button_size.y / 10);
	_confirm_server_creation_button->set_geometry(_area - anchor - button_size, button_size);

	_cancel_server_creation_button->selected_box().set_border_size(button_size.y / 10);
	_cancel_server_creation_button->unselected_box().set_border_size(button_size.y / 10);
	_cancel_server_creation_button->set_geometry(_area - anchor - button_size - jgl::Vector2Int(button_size.x * 1.2f, 0), button_size);
}

void Server_creator_menu::_render()
{

}

void Server_creator_menu::start()
{
	_server_name_entry->set_text("New Server");
	_server_ip_entry->set_text("");
}

Server_creator_menu::Server_creator_menu(std::function< void(jgl::Data_contener&) > p_funct_confirm, std::function< void(jgl::Data_contener&) > p_funct_cancel, jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_server_name_label = new jgl::Text_label("Server name : ", this);
	_server_name_label->label().set_horizontal_align(jgl::Horizontal_alignment::Centred);
	_server_name_label->label().set_vertical_align(jgl::Vertical_alignment::Centred);
	_server_name_label->box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_server_name_label->activate();

	_server_name_entry = new jgl::Text_entry("", this);
	_server_name_entry->label().set_horizontal_align(jgl::Horizontal_alignment::Left);
	_server_name_entry->label().set_vertical_align(jgl::Vertical_alignment::Centred);
	_server_name_entry->box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_server_name_entry->activate();




	_server_ip_label = new jgl::Text_label("Server ip :", this);
	_server_ip_label->label().set_horizontal_align(jgl::Horizontal_alignment::Centred);
	_server_ip_label->label().set_vertical_align(jgl::Vertical_alignment::Centred);
	_server_ip_label->box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_server_ip_label->activate();

	_server_ip_entry = new jgl::Text_entry("", this);
	_server_ip_entry->label().set_horizontal_align(jgl::Horizontal_alignment::Left);
	_server_ip_entry->label().set_vertical_align(jgl::Vertical_alignment::Centred);
	_server_ip_entry->box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_server_ip_entry->activate();


	_confirm_server_creation_button = new jgl::Button(p_funct_confirm, this);
	_confirm_server_creation_button->label().set_text("Confirm");
	_confirm_server_creation_button->selected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_selected_texture());
	_confirm_server_creation_button->unselected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_confirm_server_creation_button->activate();

	_cancel_server_creation_button = new jgl::Button(p_funct_cancel, this);
	_cancel_server_creation_button->label().set_text("Cancel");
	_cancel_server_creation_button->selected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_selected_texture());
	_cancel_server_creation_button->unselected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_cancel_server_creation_button->activate();
}