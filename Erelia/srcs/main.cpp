#include "erelia.h"


class Map
{
public:
	static const jgl::Size_t C_SIZE = 12u;
	struct Node
	{
		static const jgl::Size_t C_SIZE = 16u;

	};
	struct Area
	{
		static const jgl::Size_t C_SIZE = 16u;

		jgl::Bool content[Area::C_SIZE][Area::C_SIZE];

		Area()
		{
			for (jgl::Size_t i = 0; i < Area::C_SIZE; i++)
			{
				for (jgl::Size_t j = 0; j < Area::C_SIZE; j++)
				{
					content[i][j] = 0;
				}
			}
		}

		void randomize()
		{
			for (jgl::Size_t i = 0; i < Area::C_SIZE; i++)
			{
				for (jgl::Size_t j = 0; j < Area::C_SIZE; j++)
				{
					content[i][j] = jgl::generate_nbr(0, 2);
				}
			}
		}
	};

private:

	Area* _areas[Map::C_SIZE][Map::C_SIZE];

	jgl::Vector2Int convert_world_to_area(jgl::Vector2Int p_pos)
	{
		jgl::Vector2 result;

		result.x = static_cast<jgl::Float>(p_pos.x) / static_cast<jgl::Float>(Map::Area::C_SIZE);
		result.y = static_cast<jgl::Float>(p_pos.y) / static_cast<jgl::Float>(Map::Area::C_SIZE);

		result = result.floor();

		return (result);
	}

	jgl::Vector2Int convert_area_to_world(jgl::Vector2Int p_area_pos, jgl::Vector2Int p_pos)
	{
		return (p_area_pos * Map::Area::C_SIZE + p_pos);
	}

	jgl::Vector2Int _calc_next_space(jgl::Vector2Int p_pos)
	{
		jgl::Vector2Int result = 1;

		if (p_pos.x != Map::C_SIZE - 1)
			result.x = jgl::generate_nbr(1, Map::C_SIZE - p_pos.x);
		if (p_pos.y != Map::C_SIZE - 1)
			result.y = jgl::generate_nbr(1, Map::C_SIZE - p_pos.y);

		return (result);
	}

public:
	Map()
	{
		for (jgl::Size_t i = 0; i < Map::C_SIZE; i++)
		{
			for (jgl::Size_t j = 0; j < Map::C_SIZE; j++)
			{
				_areas[i][j] = new Area();
			}
		}
	}

	Area* area(jgl::Int p_x, jgl::Int p_y)
	{
		if (p_x < 0 || p_y < 0 || p_x >= Map::C_SIZE || p_y >= Map::C_SIZE)
			return (nullptr);
		return (_areas[p_x][p_y]);
	}

	void generate()
	{
		jgl::Bool placed_area[Map::C_SIZE][Map::C_SIZE];

		for (jgl::Size_t i = 0; i < Map::C_SIZE; i++)
		{
			for (jgl::Size_t j = 0; j < Map::C_SIZE; j++)
			{
				Area* tmp_area = _areas[i][j];
				tmp_area->randomize();
				placed_area[i][j] = false;
			}
		}


		for (jgl::Size_t i = 0; i < Map::C_SIZE;i++)
		{
			for (jgl::Size_t j = 0; j < Map::C_SIZE;j++)
			{
				if (placed_area[i][j] == false)
				{
					jgl::cout << "New pos to calc : " << i << " / " << j << jgl::endl;

					jgl::Vector2Int size = _calc_next_space(jgl::Vector2Int(i, j));

					jgl::cout << "New area size : " << size << jgl::endl;
					for (jgl::Size_t x = 0; x < size.x; x++)
					{
						for (jgl::Size_t y = 0; y < size.y; y++)
						{
							placed_area[i + x][j + y] = true;
						}
					}
				}
			}
		}
	}

};

int main(int argc, char **argv)
{
	jgl::Application app = jgl::Application("Erelia", jgl::Vector2Int(1200, 640), jgl::Color(50, 50, 50));
	app.add_shader_from_file("Area shader", "ressource/shader/area_shader.vert", "ressource/shader/area_shader.frag");
	app.set_default_font("ressource/font/karma suture.ttf");
	app.active_multithread();

	Map map;

	map.generate();

	jgl::Vector2Int size = jgl::Vector2Int(Map::C_SIZE * Map::Area::C_SIZE * Map::Node::C_SIZE, Map::C_SIZE * Map::Area::C_SIZE * Map::Node::C_SIZE);
	jgl::Image_output* output = new jgl::Image_output(size);

	output->associate();

	jgl::draw_rectangle_color(jgl::Color(50, 50, 50), 0, size, 0);

	for (jgl::Size_t i = 0; i < Map::C_SIZE; i++)
	{
		for (jgl::Size_t j = 0; j < Map::C_SIZE; j++)
		{
			jgl::Vector2Int area_pos = jgl::Vector2Int(i, j) * Map::Area::C_SIZE * Map::Node::C_SIZE;
			Map::Area* tmp_area = map.area(i, j);

			for (jgl::Size_t x = 0; x < Map::Area::C_SIZE; x++)
			{
				for (jgl::Size_t y = 0; y < Map::Area::C_SIZE; y++)
				{
					if (tmp_area->content[x][y] == 1)
					{
						jgl::Vector2Int node_pos = jgl::Vector2Int(x, y) * Map::Node::C_SIZE;

						jgl::draw_rectangle_color(jgl::Color::white(), node_pos + area_pos, Map::Node::C_SIZE, 1);
					}
				}
			}
		}
	}

	output->save_to_png("Result.png");

	return (0);
}