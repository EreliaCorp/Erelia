#include "erelia.h"

void World_selecter_menu::_on_geometry_change()
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
		_world_loader_button_array[i]->set_geometry(anchor, button_size);
		_world_loader_button_array[i]->selected_box().set_border_size(button_size.y / 10);
		_world_loader_button_array[i]->unselected_box().set_border_size(button_size.y / 10);
		anchor.y += button_size.y * 1.2f;

	}
	_down_slider_button->set_geometry(anchor + jgl::Vector2Int((button_size.x - slider_size.x) / 2, 0), slider_size);
	_down_slider_button->selected_box().set_border_size(slider_size.y / 10);
	_down_slider_button->unselected_box().set_border_size(slider_size.y / 10);
	anchor.y += slider_size.y + button_size.y * 0.2f;


	_new_world_button->set_geometry(anchor, button_size);
	_new_world_button->selected_box().set_border_size(button_size.y / 10);
	_new_world_button->unselected_box().set_border_size(button_size.y / 10);
}

void World_selecter_menu::_render()
{

}

void World_selecter_menu::_load_world_list()
{
	_file_list = jgl::list_files(Path_atlas::world_path, "");

	for (jgl::Int i = 0; i < 4; i++)
	{
		if (i + _world_list_start < _file_list.size())
		{
			_world_loader_button_array[i]->label().set_text(_file_list[i + _world_list_start].substr(Path_atlas::world_path.size(), _file_list[i + _world_list_start].size() - Path_atlas::world_path.size()));
		}
		else
		{
			_world_loader_button_array[i]->label().set_text("");
		}
	}
}

void World_selecter_menu::start()
{
	_world_list_start = 0;
	_load_world_list();
}

jgl::String World_selecter_menu::selected_world()
{
	for (jgl::Size_t i = 0; i < _world_loader_button_array.size(); i++)
	{
		if (_world_loader_button_array[i]->is_pointed() == true)
			return (_world_loader_button_array[i]->label().text());
	}
	return ("");
};
World_selecter_menu::World_selecter_menu(std::function< void(jgl::Data_contener&) > p_funct_load, std::function< void(jgl::Data_contener&) > p_funct_create, jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_up_slider_button = new jgl::Button([&](jgl::Data_contener& p_param) {if (_world_list_start > 0) { _world_list_start--; _load_world_list(); } }, this);
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

		_world_loader_button_array.push_back(tmp_button);
	}

	_down_slider_button = new jgl::Button([&](jgl::Data_contener& p_param) {if (_world_list_start + 1 < _file_list.size()) { _world_list_start++; _load_world_list(); } }, this);
	_down_slider_button->label().set_text("Down");
	_down_slider_button->selected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_selected_texture());
	_down_slider_button->unselected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_down_slider_button->activate();

	_new_world_button = new jgl::Button(p_funct_create, this);
	_new_world_button->label().set_text("New world");
	_new_world_button->selected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_selected_texture());
	_new_world_button->unselected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_new_world_button->activate();
}