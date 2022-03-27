#include "widget/Screen/Game_world/Widget/erelia_map_renderer.h"
#include "structure/data/engine/erelia_engine.h"
#include  "widget/Screen/Game_world/erelia_game_world_screen.h"

void Map_renderer::_on_geometry_change()
{

}

void Map_renderer::_render()
{
	jgl::Vector2Int start = convert_screen_to_chunk(0);
	jgl::Vector2Int end = convert_screen_to_chunk(_area);
	Map* map = Engine::instance()->map();

	jgl::Int animation_state = (jgl::Application::active_application()->time() % 1000) / 250;

	if (Node::size < 4)
		animation_state = 0;

	if (map == nullptr)
		return;

	for (jgl::Int x = start.x; x <= end.x; x++)
	{
		for (jgl::Int y = start.y; y <= end.y; y++)
		{
			jgl::Vector2Int chunk_pos = jgl::Vector2Int(x, y);
			Chunk* tmp_chunk = map->chunk(chunk_pos);

			if (tmp_chunk != nullptr)
			{
				if (tmp_chunk->baked() == false)
					tmp_chunk->bake(map, true);

				tmp_chunk->render(jgl::convert_screen_to_opengl(convert_chunk_to_screen(chunk_pos), _depth), animation_state);
				if (Game_world_screen::Publisher::instance()->context()->area_mode == true)
					tmp_chunk->render_area(jgl::convert_screen_to_opengl(convert_chunk_to_screen(chunk_pos), _depth), animation_state);
			}
		}
	}
}

Map_renderer::Map_renderer(jgl::Widget* p_parent) : Overworld_widget(p_parent)
{
	
}