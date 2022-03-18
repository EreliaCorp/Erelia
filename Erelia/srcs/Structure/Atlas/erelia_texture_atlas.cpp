#include "erelia.h"

Texture_atlas::Texture_atlas()
{

}

Texture_atlas* Texture_atlas::_instance = nullptr;

Texture_atlas* Texture_atlas::instanciate()
{
	_instance = new Texture_atlas();
	return (_instance);
}

Texture_atlas* Texture_atlas::instance()
{
	return (_instance);
}

void Texture_atlas::add_texture(jgl::String p_name, jgl::Image_handler* p_image_handler)
{
	if (_content[p_name] != nullptr)
		delete _content[p_name];
	_content[p_name] = p_image_handler;
	if (p_name == Path_atlas::basic_frame_texture_name)
	{
		_basic_frame = static_cast<jgl::Sprite_sheet*>(p_image_handler);
	}
	else if (p_name == Path_atlas::basic_frame_texture_pressed_name)
	{
		_basic_frame_selected = static_cast<jgl::Sprite_sheet*>(p_image_handler);
	}
	else if (p_name == Path_atlas::chunk_sprite_sheet_name)
	{
		_node_sprite_sheet = static_cast<jgl::Sprite_sheet*>(p_image_handler);
	}
	else if (p_name == Path_atlas::prefab_sprite_sheet_name)
	{
		_prefab_sprite_sheet = static_cast<jgl::Sprite_sheet*>(p_image_handler);
	}
	else if (p_name == Path_atlas::UI_sprite_sheet_name)
	{
		_UI_sprite_sheet = static_cast<jgl::Sprite_sheet*>(p_image_handler);
	}
	else if (p_name == Path_atlas::monster_area_sprite_sheet_name)
	{
		_monster_area_sheet = static_cast<jgl::Sprite_sheet*>(p_image_handler);
	}
}

jgl::Image_handler* Texture_atlas::get_texture(jgl::String p_name)
{
	if (_content.count(p_name) == 0)
		return (nullptr);
	return (_content[p_name]);
}