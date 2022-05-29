#include "Generator/erelia_map_generator.h"
#include "widget/screen/game_world/Widget/erelia_map_operation.h"

namespace Map_generator
{
	void generate_node_tiles(jgl::String p_path)
	{
		THROW_INFORMATION("Generating node tiles");
		jgl::Image test = jgl::Image(p_path);

		jgl::Array<jgl::Uint> values = { 5735679, 832762623, 2748196863, 1149836031, 4158811135, 1228680191, 2644352511, 2300212991, 2758025983 };

		jgl::Array<jgl::Uint> values_node = { 14, 13, 0, 1, 2, 3, 5, 7 , 4 };

		jgl::Array<jgl::String> values_text = { "Deep water", "Water", "Plain", "Forest" , "Sand", "Montain", "Rock", "Enchanted forest", "Road" };

		for (jgl::Size_t y = 0; y < test.height(); y++)
		{
			THROW_INFORMATION("Generating node tiles - Line " + jgl::itoa(y) + " / " + jgl::itoa(test.height()));
			for (jgl::Size_t x = 0; x < test.width(); x++)
			{
				jgl::Uint result = test.pixel(x, y);
				jgl::String text_result = "Unknow";
				jgl::Uint node_result = -1;
				for (jgl::Size_t i = 0; i < values.size(); i++)
					if (values[i] == result)
					{
						node_result = values_node[i];
						text_result = values_text[i];
					}
				if (node_result == -1)
				{
					jgl::cout << "Node value : " << result << " at pos " << x << " / " << y << jgl::endl;
				}

				if (Engine::instance() == nullptr)
					Engine::instance()->instanciate();
				if (Engine::instance()->map()->chunk(Map::convert_world_to_chunk(jgl::Vector2Int(x, y))) == nullptr)
					Engine::instance()->map()->add_chunk(Engine::instance()->map()->request_chunk(Map::convert_world_to_chunk(jgl::Vector2Int(x, y))));
				if (Engine::instance()->map()->chunk(Map::convert_world_to_chunk(jgl::Vector2Int(x, y))) != nullptr)
				{
					Engine::instance()->map()->place_node(jgl::Vector3Int(x, y, 0), node_result);
				}
			}
		}
	}
}