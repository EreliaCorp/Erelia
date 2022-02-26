#pragma once

#include "jgl.h"

class Path_atlas
{
private:
	Path_atlas() = delete;

public:
	static const jgl::String world_path;
	static const jgl::String ui_configuration_path;
	static const jgl::String ui_configuration_file;
	static const jgl::String basic_frame_texture_path;
	static const jgl::String basic_frame_texture_pressed_path;
	static const jgl::String chunk_sprite_sheet_path;
	static void compose_ressource_folder();
	static void compose_world_folder(jgl::String p_world_name);
};