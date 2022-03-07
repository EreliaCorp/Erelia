#pragma once

#include "jgl.h"

#include "Structure/Data/Map/erelia_node.h"

class Chunk
{
public:
	static const jgl::Size_t C_SIZE = 16u;
	static const jgl::Size_t C_LAYER_LENGTH = 7u;
	static const jgl::Size_t C_NB_ANIMATION_FRAME = 4u;

private:
	struct Shader_data
	{
		static jgl::Shader* shader;

		jgl::Bool generated = false;

		jgl::Buffer* model_space_buffer = nullptr;
		jgl::Buffer* model_uvs_buffer = nullptr;
		jgl::Buffer* animation_sprite_delta_buffer = nullptr;
		jgl::Buffer* indexes_buffer = nullptr;

		jgl::Uniform* delta_model_uniform = nullptr;
		jgl::Uniform* animation_state_uniform = nullptr;
		jgl::Uniform* uvs_unit_uniform = nullptr;
		jgl::Uniform* texture_uniform = nullptr;

		void generate();
		void cast(jgl::Vector3 p_offset, jgl::Int p_animation_state);
	};

	Shader_data _shader_data;

	jgl::Vector2Int _pos;
	jgl::Short _content[C_SIZE][C_SIZE][C_LAYER_LENGTH];

	static jgl::Vector3 _delta_autotile_position[4];
	static jgl::Vector3 _delta_tile_position[4];
	static jgl::Vector2 _delta_uvs[4];
	static jgl::Uint _delta_indexes[6];
	static jgl::Vector2Int _baking_neightbour_node[4][3];
	static jgl::Vector2Int _baking_delta_node_sprite[4][2][2][2];
	static jgl::Vector3 _screen_node_unit;

	jgl::Bool _baked = false;

	void _initialize_opengl_data();

	jgl::Vector2Int _calc_sub_part_sprite(jgl::Int p_x, jgl::Int p_y, jgl::Int p_z, jgl::Size_t p_sub_part);

	void _bake_autotile(jgl::Array<jgl::Vector3>& p_vertex_array, jgl::Array<jgl::Vector2>& p_uvs_array, jgl::Array<jgl::Float>& p_animation_sprite_delta_array, jgl::Array<jgl::Uint>& p_element_array, Node* p_node, jgl::Int p_x, jgl::Int p_y, jgl::Int p_z);

	void _bake_tile(jgl::Array<jgl::Vector3>& p_vertex_array, jgl::Array<jgl::Vector2>& p_uvs_array, jgl::Array<jgl::Float>& p_animation_sprite_delta_array, jgl::Array<jgl::Uint>& p_element_array, Node* p_node, jgl::Int p_x, jgl::Int p_y, jgl::Int p_z);

	Chunk* _neightbour_chunks[3][3];
public:
	static jgl::String compose_chunk_file_name(jgl::String p_path, jgl::Vector2Int p_pos);

public:
	Chunk(jgl::Vector2Int p_pos = 0);

	void save(jgl::String p_folder_path);
	void load(jgl::String p_path);

	jgl::Bool baked() { return (_baked); }
	void unbake();
	void bake(class Map* p_map, jgl::Bool rebake);

	void render(jgl::Vector3 p_offset, jgl::Int p_animation_state);

	jgl::Vector2Int pos() { return (_pos); }

	void set_content(jgl::Vector2Int p_pos, jgl::Size_t p_level, jgl::Short p_value);
	void set_content(jgl::Vector3Int p_pos, jgl::Short p_value);

	jgl::Short* content() { return (&(_content[0][0][0])); }
	jgl::Short content(jgl::Vector2Int p_pos, jgl::Size_t p_level);
	jgl::Short content(jgl::Vector3Int p_pos);

	Node* node(jgl::Vector2Int p_pos, jgl::Size_t p_level);
	Node* node(jgl::Vector3Int p_pos);

	static jgl::Vector3Int convert_absolute_to_relative_pos(jgl::Vector2Int p_pos, jgl::Size_t p_level);
	static jgl::Vector3Int convert_absolute_to_relative_pos(jgl::Vector3Int p_pos);

	static jgl::Vector3Int convert_relative_to_absolute_pos(jgl::Vector2Int p_chunk_pos, jgl::Vector2Int p_pos, jgl::Size_t p_level);
	static jgl::Vector3Int convert_relative_to_absolute_pos(jgl::Vector2Int p_chunk_pos, jgl::Vector3Int p_pos);

	jgl::Vector3Int convert_relative_to_absolute_pos(jgl::Vector2Int p_pos, jgl::Size_t p_level);
	jgl::Vector3Int convert_relative_to_absolute_pos(jgl::Vector3Int p_pos);
};