#pragma once

#include "jgl.h"

class Texture_atlas
{
private:
	jgl::Map<jgl::String, jgl::Image_handler*> _content;
	jgl::Sprite_sheet* _basic_frame = nullptr;
	jgl::Sprite_sheet* _basic_frame_selected = nullptr;
	jgl::Sprite_sheet* _node_sprite_sheet = nullptr;
	jgl::Sprite_sheet* _prefab_sprite_sheet = nullptr;

	Texture_atlas();
	static Texture_atlas* _instance;

public:
	static Texture_atlas* instanciate();

	static Texture_atlas* instance();

	void add_texture(jgl::String p_name, jgl::Image_handler* p_image_handler);
	jgl::Image_handler* get_texture(jgl::String p_name);
	jgl::Sprite_sheet* basic_frame_texture() { return (_basic_frame); }
	jgl::Sprite_sheet* basic_frame_selected_texture() { return (_basic_frame_selected); }
	jgl::Sprite_sheet* node_sprite_sheet() { return (_node_sprite_sheet); }
	jgl::Sprite_sheet* prefab_sprite_sheet() { return (_prefab_sprite_sheet); }
};