#include "erelia.h"

Map_renderer::Map_renderer(jgl::Widget* p_parent) : Graphical_widget(p_parent)
{

}

void Map_renderer::_on_geometry_change()
{
	Engine::instance()->map()->unbake();
}

void Map_renderer::_render()
{
	if (Engine::instance()->player() == nullptr || Engine::instance()->map() == nullptr)
		return ;

	jgl::Vector2Int start = convert_screen_to_chunk(0);
	jgl::Vector2Int end = convert_screen_to_chunk(_area);
	Map* map = Engine::instance()->map();

	jgl::Int animation_state = (jgl::Application::active_application()->time() % 1000) / 250;

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
			}
		}
	}
}