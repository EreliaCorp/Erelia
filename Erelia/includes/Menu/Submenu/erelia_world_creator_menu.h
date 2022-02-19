#pragma once

#include "jgl.h"

class World_creator_menu : public jgl::Widget
{
private:
	jgl::Text_label* _world_name_label;
	jgl::Text_entry* _world_name_entry;

	jgl::Text_label* _world_seed_label;
	jgl::Text_entry* _world_seed_entry;
	jgl::Button* _world_seed_randomizer_button;

	jgl::Button* _confirm_world_creation_button;
	jgl::Button* _cancel_world_creation_button;

	void _on_geometry_change();
	void _render();

public:
	World_creator_menu(std::function< void(jgl::Data_contener&) > p_funct_confirm, std::function< void(jgl::Data_contener&) > p_funct_cancel, jgl::Widget* p_parent);

	void start();

	jgl::String world_name() { return (_world_name_entry->label().text()); }
};