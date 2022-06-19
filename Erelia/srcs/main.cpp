#include "erelia.h"


class Map
{
public:
	static const jgl::Size_t C_SIZE = 12u;
	struct Node
	{
		static const jgl::Size_t C_SIZE = 16u;

		static const jgl::Size_t C_EMPTY_NODE = 0;
		static const jgl::Size_t C_WALL_NODE = 1;

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
					content[i][j] = Map::Node::C_EMPTY_NODE;
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

	jgl::Bool _placed_areas[Map::C_SIZE][Map::C_SIZE];
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
		jgl::Vector2Int max_size = 0;

		for (; max_size.x < 4 && p_pos.x + max_size.x < Map::C_SIZE && _placed_areas[p_pos.x + max_size.x][p_pos.y] == false; max_size.x++);
		for (; max_size.y < 4 && p_pos.y + max_size.y < Map::C_SIZE && _placed_areas[p_pos.x][p_pos.y + max_size.y] == false; max_size.y++);

		return (jgl::Vector2Int(
				jgl::generate_nbr(1, max_size.x),
				jgl::generate_nbr(1, max_size.y)
			)
		);
	}

	void _place_next_sub_area(jgl::Vector2Int p_pos, jgl::Vector2Int p_size)
	{
		for (jgl::Size_t x = 0; x < p_size.x; x++)
		{
			for (jgl::Size_t y = 0; y < p_size.y; y++)
			{
				_placed_areas[p_pos.x + x][p_pos.y + y] = true;
			}
		}

		for (jgl::Size_t x = 0; x < p_size.x * Map::Area::C_SIZE; x++)
		{
			for (jgl::Size_t y = 0; y < p_size.y * Map::Area::C_SIZE; y++)
			{
				if (x == 0 || y == 0 || x == p_size.x * Map::Area::C_SIZE - 1 || y == p_size.y * Map::Area::C_SIZE - 1)
					set_content(p_pos.x * Map::Area::C_SIZE + x, p_pos.y * Map::Area::C_SIZE + y, Map::Node::C_WALL_NODE);
			}
		}
	}

	void _print_placed_tab()
	{
		jgl::cout << "State : " << jgl::endl;
		for (jgl::Size_t j = 0; j < Map::C_SIZE; j++)
		{
			for (jgl::Size_t i = 0; i < Map::C_SIZE; i++)
			{
				jgl::cout << "[" << (_placed_areas[i][j] == true ? "X" : " ") << "]";
			}
			jgl::cout << jgl::endl;
		}
		jgl::cout << jgl::endl;
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

	jgl::Size_t content(jgl::Vector2Int p_pos)
	{
		content(p_pos.x, p_pos.y);
	}

	jgl::Size_t content(jgl::Int p_x, jgl::Int p_y)
	{
		jgl::Vector2Int chunk_pos = convert_world_to_area(jgl::Vector2Int(p_x, p_y));
		Area* tmp_area = area(chunk_pos.x, chunk_pos.y);

		if (tmp_area != nullptr)
		{
			return (tmp_area->content[p_x - chunk_pos.x * Map::Area::C_SIZE][p_y - chunk_pos.y * Map::Area::C_SIZE]);
		}
		else
			return (Map::Node::C_EMPTY_NODE);
	}

	void set_content(jgl::Vector2Int p_pos, jgl::Size_t p_value)
	{
		set_content(p_pos.x, p_pos.y, p_value);
	}

	void set_content(jgl::Int p_x, jgl::Int p_y, jgl::Size_t p_value)
	{
		jgl::Vector2Int chunk_pos = convert_world_to_area(jgl::Vector2Int(p_x, p_y));
		Area* tmp_area = area(chunk_pos.x, chunk_pos.y);

		if (tmp_area != nullptr)
		{
			tmp_area->content[p_x - chunk_pos.x * Map::Area::C_SIZE][p_y - chunk_pos.y * Map::Area::C_SIZE] = p_value;
		}
	}

	void _randomize()
	{
		for (jgl::Size_t i = 0; i < Map::C_SIZE; i++)
		{
			for (jgl::Size_t j = 0; j < Map::C_SIZE; j++)
			{
				Area* tmp_area = _areas[i][j];
				tmp_area->randomize();
				_placed_areas[i][j] = false;
			}
		}
	}

	void _generate_border()
	{
		for (jgl::Size_t i = 0; i < Map::C_SIZE; i++)
		{
			for (jgl::Size_t j = 0; j < Map::C_SIZE; j++)
			{
				if (_placed_areas[i][j] == false)
				{
					jgl::Vector2Int pos = jgl::Vector2Int(i, j);
					jgl::Vector2Int size = _calc_next_space(pos);

					_place_next_sub_area(pos, size);
				}
			}
		}
	}

	void generate()
	{
		_randomize();

		for (jgl::Size_t i = 0; i < Map::C_SIZE;i++)
		{
			for (jgl::Size_t j = 0; j < Map::C_SIZE;j++)
			{
				if (_placed_areas[i][j] == false)
				{
					jgl::Vector2Int pos = jgl::Vector2Int(i, j);
					jgl::Vector2Int size = _calc_next_space(pos);

					_place_next_sub_area(pos, size);
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
					if (tmp_area->content[x][y] == 0)
					{
						jgl::Vector2Int node_pos = jgl::Vector2Int(x, y) * Map::Node::C_SIZE + area_pos;
						node_pos.y = size.y - node_pos.y;

						jgl::draw_rectangle_color(jgl::Color::white(), node_pos, Map::Node::C_SIZE, 1);
					}
				}
			}
		}
	}

	output->save_to_png("Result.png");

	return (0);
}