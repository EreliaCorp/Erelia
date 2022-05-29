#include "Generator/erelia_map_generator.h"
#include "widget/screen/game_world/Widget/erelia_map_operation.h"

namespace Map_generator
{
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
}