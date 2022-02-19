#include "erelia.h"

Graphical_widget::Graphical_widget(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{

}

jgl::Vector2Int Graphical_widget::convert_world_to_screen(jgl::Vector2 p_pos)
{
	jgl::Vector2 player_pos = Engine::instance()->player()->pos();

	jgl::Vector2Int result = (p_pos - player_pos) * Node::C_SIZE + _area / 2;
	return (result);
}

jgl::Vector2 Graphical_widget::convert_screen_to_world(jgl::Vector2Int p_pos)
{
	jgl::Vector2 player_pos = Engine::instance()->player()->pos();

	jgl::Vector2 result = p_pos - _area / 2;
	result /= Node::C_SIZE;
	result += player_pos;
	return (result);
}

jgl::Vector2Int Graphical_widget::convert_screen_to_chunk(jgl::Vector2Int p_pos)
{
	jgl::Vector2 result = convert_screen_to_world(p_pos);
	result /= Chunk::C_SIZE;
	return (result.floor());
}