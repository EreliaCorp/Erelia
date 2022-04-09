#include "widget/Abstract_widget/erelia_overworld_widget.h"
#include "structure/data/engine/erelia_engine.h"
#include "structure/data/map/erelia_chunk.h"

jgl::Vector2Int Overworld_widget::convert_world_to_screen(jgl::Vector2 p_pos)
{
	jgl::Vector2 player_pos = Engine::instance()->player()->pos();

	jgl::Vector2Int result = (p_pos - player_pos) * Node::size + _area / 2;
	return (result);
}

jgl::Vector2Int Overworld_widget::convert_chunk_to_screen(jgl::Vector2Int p_pos)
{
	return (convert_world_to_screen(p_pos * Chunk::C_SIZE));
}

jgl::Vector2 Overworld_widget::convert_screen_to_world(jgl::Vector2Int p_pos)
{
	jgl::Vector2 player_pos = Engine::instance()->player()->pos();

	jgl::Vector2 result = p_pos - _area / 2;
	result /= Node::size;
	result += player_pos;
	result = result.floor();

	return (result);
}

jgl::Vector2Int Overworld_widget::convert_screen_to_chunk(jgl::Vector2Int p_pos)
{
	jgl::Vector2 result = convert_screen_to_world(p_pos);
	result /= Chunk::C_SIZE;
	return (result.floor());
}

Overworld_widget::Overworld_widget(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{

}