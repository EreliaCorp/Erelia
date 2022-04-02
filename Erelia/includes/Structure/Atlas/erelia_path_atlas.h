#pragma once

#include "jgl.h"

class Path_atlas
{
private:
	Path_atlas() = delete;

public:
	static const jgl::String ui_config_path;

	static const jgl::String world_path;
	static const jgl::String player_sub_path;
	static const jgl::String player_save_extension;
	static const jgl::String wrap_sub_path;
	static const jgl::String wrap_name_file;
	static const jgl::String wrap_save_extension;
	static const jgl::String chunk_name_file;
	static const jgl::String chunk_sub_path;
	static const jgl::String chunk_extension;

	static const jgl::String default_language_file;
	static const jgl::String language_folder_path;
	static const jgl::String language_file_extension;
	static const jgl::String erelia_logo_path;

	static const jgl::String encounter_area_subpath;
	static const jgl::String encounter_area_name;
	static const jgl::String encounter_area_extension;

	static const jgl::String monster_folder_path;
	static const jgl::String monster_file_extension;

	static const jgl::String basic_frame_texture_name;
	static const jgl::String basic_frame_texture_path;

	static const jgl::String basic_frame_texture_pressed_name;
	static const jgl::String basic_frame_texture_pressed_path;

	static const jgl::String chunk_sprite_sheet_name;
	static const jgl::String chunk_sprite_sheet_path;

	static const jgl::String prefab_sprite_sheet_name;
	static const jgl::String prefab_sprite_sheet_path;

	static const jgl::String UI_sprite_sheet_name;
	static const jgl::String UI_sprite_sheet_path;

	static const jgl::String monster_area_sprite_sheet_name;
	static const jgl::String monster_area_sprite_sheet_path;
};