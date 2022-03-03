#include "erelia.h"

Map_loader::Map_loader(jgl::Widget* p_parent) : Graphical_widget(p_parent)
{

}

void Map_loader::_on_geometry_change()
{

}

jgl::Bool Map_loader::_update()
{
	if (Engine::instance()->player() == nullptr || Engine::instance()->map() == nullptr)
		return false;

	Map* map = Engine::instance()->map();

	jgl::Vector2Int start = convert_screen_to_chunk(0);
	jgl::Vector2Int end = convert_screen_to_chunk(_area);

	for (jgl::Int x = start.x; x <= end.x; x++)
	{
		for (jgl::Int y = start.y; y <= end.y; y++)
		{
			jgl::Vector2Int chunk_pos = jgl::Vector2Int(x, y);

			if (map->chunk(chunk_pos) == nullptr)
			{
				jgl::cout << "Loading chunk " << chunk_pos << jgl::endl;
				map->request_chunk(chunk_pos);
			}
		}
	}

	return (false);
}

void Map_loader::_render()
{
		
}