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

	void generate_wall_tiles(jgl::String p_path)
	{
		jgl::Image test = jgl::Image(p_path);

		jgl::Array<jgl::Uint> layers = { 0xffffff00, 0xff0000ff, 0x0000ffff, 0x00ff00ff, 0x00ffffff, 0xffff00ff, 0xffffffff };

		for (jgl::Size_t target = 1; target < layers.size(); target++)
		{
			THROW_INFORMATION("Generating layers - Layer " + jgl::itoa(target) + " / " + jgl::itoa(layers.size()));
			for (jgl::Size_t j = 0; j < test.height(); j++)
			{
				THROW_INFORMATION("Generating layers [" + jgl::itoa(target) + "] tiles - Line " + jgl::itoa(j) + " / " + jgl::itoa(test.height()));
				for (jgl::Size_t i = 0; i < test.width(); i++)
				{
					jgl::Uint pixel = test.pixel(jgl::Vector2Uint(i, j));

					int height = 0;
					for (jgl::Size_t h = 0; h < layers.size(); h++)
					{
						if (pixel == layers[h])
							height = h;
					}

					if (height >= target)
					{
						Engine::instance()->map()->place_node(jgl::Vector2Int(i, j), 1, 12);
					}
				}
			}
			for (jgl::Size_t i = 0; i < test.width(); i++)
			{
				for (jgl::Size_t j = 0; j < test.height(); j++)
				{
					if (Engine::instance()->map()->content(jgl::Vector3Int(i, j, 1)) == 12)
					{
						THROW_INFORMATION("Generating wall at layer [" + jgl::itoa(target) + "] at pos : " + jgl::itoa(i) + " / " + jgl::itoa(j));
						static jgl::Array<Map_operation::Place_wall_data> to_calc;

						Map_operation::paint_wall_node_standalone(to_calc, jgl::Vector3Int(i, j, 1), 23);

						for (jgl::Size_t i = 0; i < to_calc.size(); i++)
						{
							Engine::instance()->map()->place_node(to_calc[i].pos, to_calc[i].value);
						}
					}
				}
			}
		}
	}

	void generate_biome_scenery(jgl::String p_path)
	{
		jgl::Image test = jgl::Image(p_path);
		//639 herbe +- 8
		jgl::Array<jgl::Uint> biome_color = {
			0xff0000ff,	0x00ff00ff,	0x0000ffff,	0xffff00ff,	0x00ffffff,
			0xff00ffff,	0xf2a231ff,	0x22644aff,	0x2b3c49ff,	0x9d9d9dff,
		};
		jgl::Array<jgl::Short> biome_item = {
			639,		640,		641,		642,		643,
			644,		645,		646,		639,		648
		};

		for (jgl::Size_t y = 0; y < test.height(); y++)
		{
			THROW_INFORMATION("Generating scenery - Line " + jgl::itoa(y) + " / " + jgl::itoa(test.height()));
			for (jgl::Size_t x = 0; x < test.width(); x++)
			{
				jgl::Int index = -1;
				jgl::Uint pixel_color = test.pixel(x, y);

				for (jgl::Size_t i = 0; i < biome_color.size(); i++)
					if (biome_color[i] == pixel_color)
					{
						index = i;
					}
				if (index == -1)
				{
					THROW_INFORMATION("Unknow pixel " + jgl::itoa(pixel_color));
				}

				if (index != -1)
				{
					if (Engine::instance()->map()->content(jgl::Vector3Int(x, y, 1)) == -1)
					{
						Engine::instance()->map()->place_node(jgl::Vector3Int(x, y, 1), biome_item[index]);
					}
				}
			}
		}
	}
}