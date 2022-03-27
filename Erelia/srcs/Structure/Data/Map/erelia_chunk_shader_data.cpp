#include "Structure/Data/Map/erelia_chunk.h"
#include "Structure/Atlas/erelia_texture_atlas.h"

void Chunk::Shader_data::generate()
{
	if (shader == nullptr)
		shader = jgl::Application::active_application()->shader("Chunk shader");

	for (jgl::Size_t i = 0; i < 2; i++)
	{
		if (model_space_buffer[i] == nullptr)
			model_space_buffer[i] = shader->buffer("model_space")->copy();
		if (model_uvs_buffer[i] == nullptr)
			model_uvs_buffer[i] = shader->buffer("model_uvs")->copy();
		if (animation_sprite_delta_buffer[i] == nullptr)
			animation_sprite_delta_buffer[i] = shader->buffer("animation_sprite_delta")->copy();
		if (indexes_buffer[i] == nullptr)
			indexes_buffer[i] = shader->indexes_buffer()->copy();
	}

	if (delta_model_uniform == nullptr)
		delta_model_uniform = shader->uniform("delta_model")->copy();
	if (animation_state_uniform == nullptr)
		animation_state_uniform = shader->uniform("animation_state")->copy();
	if (uvs_unit_uniform == nullptr)
		uvs_unit_uniform = shader->uniform("uvs_unit")->copy();
	if (texture_uniform == nullptr)
		texture_uniform = shader->uniform("textureID")->copy();

	generated = true;
}

void Chunk::Shader_data::cast(jgl::Vector3 p_offset, jgl::Int p_animation_state, jgl::Size_t p_index)
{
	if (p_index >= 2)
		return;

	shader->activate();

	delta_model_uniform->send(p_offset);
	animation_state_uniform->send(p_animation_state);
	if (p_index == 0)
		uvs_unit_uniform->send(Texture_atlas::instance()->node_sprite_sheet()->unit());
	else if (p_index == 1)
		uvs_unit_uniform->send(Texture_atlas::instance()->monster_area_sheet()->unit());
	texture_uniform->send(0);

	if (indexes_buffer[p_index]->size() != 0 && Texture_atlas::instance()->node_sprite_sheet() != nullptr)
	{
		if (p_index == 0)
			Texture_atlas::instance()->node_sprite_sheet()->activate();
		else if (p_index == 1)
			Texture_atlas::instance()->monster_area_sheet()->activate();

		model_space_buffer[p_index]->activate();
		model_uvs_buffer[p_index]->activate();
		animation_sprite_delta_buffer[p_index]->activate();
		indexes_buffer[p_index]->activate();

		shader->cast(jgl::Shader::Mode::Triangle, indexes_buffer[p_index]->size() / sizeof(jgl::Uint));
	}
}