#include "erelia.h"

const jgl::String Path_atlas::world_path = "ressource/world/";
const jgl::String Path_atlas::ui_configuration_path = "ressource/UI/";
const jgl::String Path_atlas::ui_configuration_file = "ui_configuration_file.xml";
const jgl::String Path_atlas::basic_frame_texture_path = "ressource/texture/basic_frame.png";
const jgl::String Path_atlas::basic_frame_texture_pressed_path = "ressource/texture/basic_frame_pressed.png";

void Path_atlas::compose_ressource_folder()
{
	_mkdir(Path_atlas::ui_configuration_path.c_str());
	_mkdir(Path_atlas::world_path.c_str());
}
void Path_atlas::compose_world_folder(jgl::String p_world_name)
{
	_mkdir((Path_atlas::world_path + p_world_name).c_str());
	_mkdir((Path_atlas::world_path + p_world_name + "/chunk/").c_str());
	_mkdir((Path_atlas::world_path + p_world_name + "/player/").c_str());
}