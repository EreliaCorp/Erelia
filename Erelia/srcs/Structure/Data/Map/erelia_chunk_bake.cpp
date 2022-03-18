#include "erelia.h"

jgl::Shader* Chunk::Shader_data::shader = nullptr;
jgl::Vector3 Chunk::_screen_node_unit = 0;

void Chunk::_initialize_opengl_data()
{
	if (_shader_data.generated == false)
		_shader_data.generate();
	if (_screen_node_unit == 0)
	{
		_screen_node_unit = jgl::convert_screen_to_opengl(Node::size, 1) - jgl::convert_screen_to_opengl(0, 0);
	}
}

void Chunk::unbake()
{
	for (jgl::Int i = -1; i <= 1; i++)
	{
		for (jgl::Int j = -1; j <= 1; j++)
		{
			_neightbour_chunks[i + 1][j + 1] = nullptr;
		}
	}
	_screen_node_unit = 0;
	_baked = false;
}

jgl::Vector2Int Chunk::_calc_sub_part_sprite(jgl::Int p_x, jgl::Int p_y, jgl::Int p_z, jgl::Size_t p_sub_part, jgl::Bool p_type)
{
	jgl::Int first_value;
	
	if (p_type == true)
		first_value = content(jgl::Vector3Int(p_x, p_y, p_z));
	else
		first_value = encounter(jgl::Vector2Int(p_x, p_y));

	jgl::Bool values[3] = { false, false, false };
	for (jgl::Size_t j = 0; j < 3; j++)
	{
		jgl::Vector2Int next_pos = jgl::Vector2Int(p_x + _baking_neightbour_node[p_sub_part][j].x, p_y + _baking_neightbour_node[p_sub_part][j].y);
		jgl::Int chunk_x = (next_pos.x == -1 ? 0 : (next_pos.x != C_SIZE ? 1 : 2));
		jgl::Int chunk_y = (next_pos.y == -1 ? 0 : (next_pos.y != C_SIZE ? 1 : 2));

		if (next_pos.x == -1)
			next_pos.x = C_SIZE - 1;
		if (next_pos.y == -1)
			next_pos.y = C_SIZE - 1;

		if (next_pos.x == C_SIZE)
			next_pos.x = 0;
		if (next_pos.y == C_SIZE)
			next_pos.y = 0;

		jgl::Int next_value;

		if (_neightbour_chunks[chunk_x][chunk_y] == nullptr)
		{
			next_value = -1;
		}
		else
		{
			if (p_type == true)
				next_value = _neightbour_chunks[chunk_x][chunk_y]->content(next_pos, p_z);
			else
				next_value = _neightbour_chunks[chunk_x][chunk_y]->encounter(next_pos);
		}
		values[j] = (next_value == first_value ? false : true);
	}

	return (_baking_delta_node_sprite[p_sub_part][values[0]][values[1]][values[2]]);
}

static jgl::Uint element_index[6] = { 0, 3, 1, 2, 3, 0 };
static jgl::Vector3 delta_autotile_pos[4] = {
	jgl::Vector3(0.0f, 0.0f, 0.0f),
	jgl::Vector3(0.5f, 0.0f, 0.0f),
	jgl::Vector3(0.0f, 0.5f, 0.0f),
	jgl::Vector3(0.5f, 0.5f, 0.0f)
};
static jgl::Vector3 delta_tile_pos[4] = {
	jgl::Vector3(0, 0, 0),
	jgl::Vector3(1, 0, 0),
	jgl::Vector3(0, 1, 0),
	jgl::Vector3(1, 1, 0)
};
static jgl::Vector2 delta_uvs[4] = {
	jgl::Vector2(0, 0),
	jgl::Vector2(1, 0),
	jgl::Vector2(0, 1),
	jgl::Vector2(1, 1)
};

void Chunk::_bake_autotile(jgl::Array<jgl::Vector3>& p_vertex_array, jgl::Array<jgl::Vector2>& p_uvs_array, jgl::Array<jgl::Float>& p_animation_sprite_delta_array, jgl::Array<jgl::Uint>& p_element_array,
	Node* p_node,
	jgl::Int p_x, jgl::Int p_y, jgl::Int p_z)
{
	for (jgl::Size_t face = 0; face < 4; face++)
	{
		jgl::Vector2Int sprite_value = p_node->sprite + _calc_sub_part_sprite(p_x, p_y, p_z, face);
		jgl::Uint sprite_id = (Texture_atlas::instance()->node_sprite_sheet()->size().x * sprite_value.y) + sprite_value.x;
		jgl::Vector3 node_pos = jgl::Vector3(p_x, p_y, p_z) + _delta_autotile_position[face];
		jgl::Vector2 sprite = Texture_atlas::instance()->node_sprite_sheet()->sprite(sprite_id);
		jgl::Vector2 unit = Texture_atlas::instance()->node_sprite_sheet()->unit();

		jgl::Size_t vertex_array_entry_size = p_vertex_array.size();

		for (size_t i = 0; i < 4; i++)
		{
			p_vertex_array.push_back(_screen_node_unit * (node_pos + delta_autotile_pos[i]));
			p_uvs_array.push_back(sprite + unit * delta_uvs[i]);
		}
		for (jgl::Size_t i = 0; i < 6; i++)
		{
			p_element_array.push_back(element_index[i] + vertex_array_entry_size);
		}

		for (jgl::Size_t i = 0; i < 4; i++)
			p_animation_sprite_delta_array.push_back(static_cast<jgl::Float>(p_node->animation_size));
	}

}

void Chunk::_bake_monster_area(jgl::Array<jgl::Vector3>& p_vertex_array, jgl::Array<jgl::Vector2>& p_uvs_array, jgl::Array<jgl::Float>& p_animation_sprite_delta_array, jgl::Array<jgl::Uint>& p_element_array,
	jgl::Vector2Int p_sprite,
	jgl::Int p_x, jgl::Int p_y)
{
	for (jgl::Size_t face = 0; face < 4; face++)
	{
		jgl::Vector2Int sprite_value = p_sprite + _calc_sub_part_sprite(p_x, p_y, 0, face, false);
		jgl::Uint sprite_id = (Texture_atlas::instance()->monster_area_sheet()->size().x * sprite_value.y) + sprite_value.x;
		jgl::Vector3 node_pos = jgl::Vector3(p_x, p_y, C_LAYER_LENGTH / 2) + _delta_autotile_position[face];
		jgl::Vector2 sprite = Texture_atlas::instance()->monster_area_sheet()->sprite(sprite_id);
		jgl::Vector2 unit = Texture_atlas::instance()->monster_area_sheet()->unit();

		jgl::Size_t vertex_array_entry_size = p_vertex_array.size();

		for (size_t i = 0; i < 4; i++)
		{
			p_vertex_array.push_back(_screen_node_unit * (node_pos + delta_autotile_pos[i]));
			p_uvs_array.push_back(sprite + unit * delta_uvs[i]);
		}
		for (jgl::Size_t i = 0; i < 6; i++)
		{
			p_element_array.push_back(element_index[i] + vertex_array_entry_size);
		}

		for (jgl::Size_t i = 0; i < 4; i++)
			p_animation_sprite_delta_array.push_back(0.0f);
	}

}

void Chunk::_bake_tile(jgl::Array<jgl::Vector3>& p_vertex_array, jgl::Array<jgl::Vector2>& p_uvs_array, jgl::Array<jgl::Float>& p_animation_sprite_delta_array, jgl::Array<jgl::Uint>& p_element_array,
	Node* p_node,
	jgl::Int p_x, jgl::Int p_y, jgl::Int p_z)
{
	jgl::Uint sprite_id = (Texture_atlas::instance()->node_sprite_sheet()->size().x * p_node->sprite.y) + p_node->sprite.x;
	jgl::Vector3 node_pos = jgl::Vector3(p_x, p_y, p_z);
	jgl::Vector2 sprite = Texture_atlas::instance()->node_sprite_sheet()->sprite(sprite_id);
	jgl::Vector2 unit = Texture_atlas::instance()->node_sprite_sheet()->unit();

	jgl::Size_t vertex_array_entry_size = p_vertex_array.size();

	for (size_t i = 0; i < 4; i++)
	{
		p_vertex_array.push_back(_screen_node_unit * (node_pos + delta_tile_pos[i]));
		p_uvs_array.push_back(sprite + unit * delta_uvs[i]);
	}
	for (jgl::Size_t i = 0; i < 6; i++)
	{
		p_element_array.push_back(element_index[i] + vertex_array_entry_size);
	}
	for (jgl::Size_t i = 0; i < 4; i++)
		p_animation_sprite_delta_array.push_back(static_cast<jgl::Float>(p_node->animation_size));
}

void Chunk::_bake_content(jgl::Array<jgl::Vector3>& p_vertex_array, jgl::Array<jgl::Vector2>& p_uvs_array, jgl::Array<jgl::Float>& p_animation_sprite_delta_array, jgl::Array<jgl::Uint>& p_element_array, jgl::Int p_x, jgl::Int p_y, jgl::Int p_z)
{
	jgl::Short value = _content[p_x][p_y][p_z];

	if (value != -1 && static_cast<jgl::Size_t>(value) < g_node_array.size())
	{
		Node* tmp_node = g_node_array[value];

		if (tmp_node->autotiled == true)
		{
			_bake_autotile(p_vertex_array, p_uvs_array, p_animation_sprite_delta_array, p_element_array, tmp_node, p_x, p_y, p_z);
		}
		else
		{
			_bake_tile(p_vertex_array, p_uvs_array, p_animation_sprite_delta_array, p_element_array, tmp_node, p_x, p_y, p_z);
		}
	}
}

void Chunk::_bake_encounter(jgl::Array<jgl::Vector3>& p_vertex_array, jgl::Array<jgl::Vector2>& p_uvs_array, jgl::Array<jgl::Float>& p_animation_sprite_delta_array, jgl::Array<jgl::Uint>& p_element_array, jgl::Int p_x, jgl::Int p_y)
{
	jgl::Int value = _encounter[p_x][p_y];

	if (value != -1)
	{
		value %= 8;
		_bake_monster_area(p_vertex_array, p_uvs_array, p_animation_sprite_delta_array, p_element_array, jgl::Vector2Int(value % 4, value / 4) * jgl::Vector2Int(4, 6), p_x, p_y);
	}
}

void Chunk::bake(Map* p_map, jgl::Bool rebake)
{
	_initialize_opengl_data();

	if (Texture_atlas::instance()->node_sprite_sheet() == nullptr)
		return ;

	for (jgl::Int i = -1; i <= 1; i++)
	{
		for (jgl::Int j = -1; j <= 1; j++)
		{
			if (_neightbour_chunks[i + 1][j + 1] == nullptr)
				_neightbour_chunks[i + 1][j + 1] = p_map->chunk(jgl::Vector2Int(i, j) + _pos);
		}
	}

	static jgl::Array<jgl::Vector3> vertex_array;
	static jgl::Array<jgl::Vector2> uvs_array;
	static jgl::Array<jgl::Float> animation_sprite_delta_array;
	static jgl::Array<jgl::Uint> element_array;

	vertex_array.clear();
	uvs_array.clear();
	animation_sprite_delta_array.clear();
	element_array.clear();

	for (jgl::Size_t i = 0; i < C_SIZE; i++)
		for (jgl::Size_t j = 0; j < C_SIZE; j++)
			for (jgl::Size_t h = 0; h < C_LAYER_LENGTH; h++)
			{
				_bake_content(vertex_array, uvs_array, animation_sprite_delta_array, element_array, i, j, h);
			}

	_shader_data.model_space_buffer[0]->send(vertex_array.all(), vertex_array.size());
	_shader_data.model_uvs_buffer[0]->send(uvs_array.all(), uvs_array.size());
	_shader_data.animation_sprite_delta_buffer[0]->send(animation_sprite_delta_array.all(), animation_sprite_delta_array.size());
	_shader_data.indexes_buffer[0]->send(element_array.all(), element_array.size());

	vertex_array.clear();
	uvs_array.clear();
	animation_sprite_delta_array.clear();
	element_array.clear();

	for (jgl::Size_t i = 0; i < C_SIZE; i++)
		for (jgl::Size_t j = 0; j < C_SIZE; j++)
			_bake_encounter(vertex_array, uvs_array, animation_sprite_delta_array, element_array, i, j);

	_shader_data.model_space_buffer[1]->send(vertex_array.all(), vertex_array.size());
	_shader_data.model_uvs_buffer[1]->send(uvs_array.all(), uvs_array.size());
	_shader_data.animation_sprite_delta_buffer[1]->send(animation_sprite_delta_array.all(), animation_sprite_delta_array.size());
	_shader_data.indexes_buffer[1]->send(element_array.all(), element_array.size());

	_baked = true;

	if (rebake == true)
	{
		for (jgl::Size_t i = 0; i < 3; i++)
		{
			for (jgl::Size_t j = 0; j < 3; j++)
			{
				if ((i != 1 || j != 1) && _neightbour_chunks[i][j] != nullptr)
					_neightbour_chunks[i][j]->bake(p_map, false);
			}
		}
	}
}

void Chunk::render(jgl::Vector3 p_offset, jgl::Int p_animation_state)
{
	if (Texture_atlas::instance()->node_sprite_sheet() != nullptr)
	{
		if (_shader_data.generated == true)
			_shader_data.cast(p_offset, p_animation_state);
	}
}