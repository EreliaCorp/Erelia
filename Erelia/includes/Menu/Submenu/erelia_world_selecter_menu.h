#pragma once

#include "jgl.h"

#include "Structure/Atlas/erelia_path_atlas.h"

class World_selecter_menu : public jgl::Widget
{
private:
	jgl::Array<jgl::String> _file_list;
	jgl::Size_t _world_list_start;

	jgl::Button* _up_slider_button;
	jgl::Array<jgl::Button*> _world_loader_button_array;
	jgl::Button* _down_slider_button;
	jgl::Button* _new_world_button;

	void _load_world_list();

	void _on_geometry_change();
	void _render();

public:
	World_selecter_menu(std::function< void(jgl::Data_contener&) > p_funct_load, std::function< void(jgl::Data_contener&) > p_funct_create, jgl::Widget* p_parent);
	jgl::String selected_world();
	void start();
};