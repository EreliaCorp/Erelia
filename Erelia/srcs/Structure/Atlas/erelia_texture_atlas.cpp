#include "Structure/Atlas/erelia_texture_atlas.h"
#include "Structure/Atlas/erelia_path_atlas.h"

Texture_atlas::Texture_atlas()
{

}

void Texture_atlas::load()
{
	add_texture(Path_atlas::basic_frame_texture_name, new jgl::Sprite_sheet(Path_atlas::basic_frame_texture_path, 3));
	add_texture(Path_atlas::basic_frame_texture_pressed_name, new jgl::Sprite_sheet(Path_atlas::basic_frame_texture_pressed_path, 3));
	add_texture(Path_atlas::chunk_sprite_sheet_name, new jgl::Sprite_sheet(Path_atlas::chunk_sprite_sheet_path, jgl::Vector2Int(32, 66)));
	add_texture(Path_atlas::prefab_sprite_sheet_name, new jgl::Sprite_sheet(Path_atlas::prefab_sprite_sheet_path, jgl::Vector2Int(8, 44)));
	add_texture(Path_atlas::UI_sprite_sheet_name, new jgl::Sprite_sheet(Path_atlas::UI_sprite_sheet_path, jgl::Vector2Int(10, 10)));
	add_texture(Path_atlas::monster_area_sprite_sheet_name, new jgl::Sprite_sheet(Path_atlas::monster_area_sprite_sheet_path, jgl::Vector2Int(16, 12)));
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