#pragma once

#include "jgl.h"

class Overworld_widget : public jgl::Widget
{
private:

public:
	Overworld_widget(jgl::Widget* p_parent);

	jgl::Vector2Int convert_chunk_to_screen(jgl::Vector2Int p_pos);
	jgl::Vector2Int convert_world_to_screen(jgl::Vector2 p_pos);
	jgl::Vector2 convert_screen_to_world(jgl::Vector2Int p_pos);
	jgl::Vector2Int convert_screen_to_chunk(jgl::Vector2Int p_pos);
};