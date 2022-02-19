#include "erelia.h"

void Server_selecter_menu::_on_geometry_change()
{
	jgl::Vector2Int slider_size = jgl::Vector2Int(_area.x / 6, _area.y / 20);
	jgl::Vector2Int button_size = jgl::Vector2Int(_area.x / 4, _area.y / 12);
	jgl::Vector2Int anchor = jgl::Vector2Int(_area.x / 2 - button_size.x / 2, _area.y / 2 - button_size.y * 1.2f - button_size.y * 1.1f - button_size.y * 0.2f - slider_size.y);

	_up_slider_button->set_geometry(anchor + jgl::Vector2Int((button_size.x - slider_size.x) / 2, 0), slider_size);
	_up_slider_button->selected_box().set_border_size(slider_size.y / 10);
	_up_slider_button->unselected_box().set_border_size(slider_size.y / 10);
	anchor.y += slider_size.y + button_size.y * 0.2f;

	for (jgl::Size_t i = 0; i < 4; i++)
	{
		_server_loader_button_array[i]->set_geometry(anchor, button_size);
		_server_loader_button_array[i]->selected_box().set_border_size(button_size.y / 10);
		_server_loader_button_array[i]->unselected_box().set_border_size(button_size.y / 10);
		anchor.y += button_size.y * 1.2f;

	}
	_down_slider_button->set_geometry(anchor + jgl::Vector2Int((button_size.x - slider_size.x) / 2, 0), slider_size);
	_down_slider_button->selected_box().set_border_size(slider_size.y / 10);
	_down_slider_button->unselected_box().set_border_size(slider_size.y / 10);
	anchor.y += slider_size.y + button_size.y * 0.2f;

	_new_server_button->set_geometry(anchor, button_size);
	_new_server_button->selected_box().set_border_size(button_size.y / 10);
	_new_server_button->unselected_box().set_border_size(button_size.y / 10);

}

void Server_selecter_menu::_render()
{
	
}

void Server_selecter_menu::_load_server_list()
{
	for (jgl::Int i = 0; i < 4; i++)
	{
		if (i + _server_list_start < Singleton_atlas::configuration_file.servers_info().size())
			_server_loader_button_array[i]->label().set_text(Singleton_atlas::configuration_file.servers_info()[i + _server_list_start].server_name);
		else
			_server_loader_button_array[i]->label().set_text("");
	}
}

void Server_selecter_menu::start()
{
	_server_list_start = 0;
	_load_server_list();
}

Server_selecter_menu::Server_selecter_menu(std::function< void(jgl::Data_contener&) > p_funct_load, std::function< void(jgl::Data_contener&) > p_funct_create, jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_server_list_start = 0;

	_up_slider_button = new jgl::Button([&](jgl::Data_contener& p_param) {if (_server_list_start > 0) { _server_list_start--; _load_server_list(); } }, this);
	_up_slider_button->label().set_text("Up");
	_up_slider_button->selected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_selected_texture());
	_up_slider_button->unselected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_up_slider_button->activate();

	for (jgl::Size_t i = 0; i < 4; i++)
	{
		jgl::Button* tmp_button = nullptr;

		tmp_button = new jgl::Button(p_funct_load, this);
		tmp_button->label().set_text("");
		tmp_button->selected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_selected_texture());
		tmp_button->unselected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
		tmp_button->activate();

		_server_loader_button_array.push_back(tmp_button);
	}

	_down_slider_button = new jgl::Button([&](jgl::Data_contener& p_param) {if (_server_list_start + 1 < Singleton_atlas::configuration_file.servers_info().size()) { _server_list_start++; _load_server_list(); } }, this);
	_down_slider_button->label().set_text("Down");
	_down_slider_button->selected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_selected_texture());
	_down_slider_button->unselected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_down_slider_button->activate();

	_new_server_button = new jgl::Button(p_funct_create, this);
	_new_server_button->label().set_text("Add new server");
	_new_server_button->selected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_selected_texture());
	_new_server_button->unselected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_new_server_button->activate();



}

UI_configuration_file::Server_info Server_selecter_menu::selected_server_info()
{
	jgl::Size_t index = _server_list_start;
	for (jgl::Size_t i = 0; i < 4; i++)
	{
		if (_server_loader_button_array[i]->is_pointed() == true)
		{
			index += i;
			break;
		}
	}

	if (index < Singleton_atlas::configuration_file.servers_info().size())
	{
		return (Singleton_atlas::configuration_file.servers_info()[index]);
	}
	else
	{
		return (UI_configuration_file::Server_info());
	}
}
