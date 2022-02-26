#include "erelia.h"

void Chunk::Shader_data::generate()
{
	if (shader == nullptr)
		shader = jgl::Application::active_application()->shader("Chunk shader");

	if (model_space_buffer == nullptr)
		model_space_buffer = shader->buffer("model_space")->copy();
	if (model_uvs_buffer == nullptr)
		model_uvs_buffer = shader->buffer("model_uvs")->copy();
	if (animation_sprite_delta_buffer == nullptr)
		animation_sprite_delta_buffer = shader->buffer("animation_sprite_delta")->copy();
	if (indexes_buffer == nullptr)
		indexes_buffer = shader->indexes_buffer()->copy();

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

void Chunk::Shader_data::cast(jgl::Vector3 p_offset, jgl::Int p_animation_state)
{
	if (indexes_buffer->size() != 0 && Chunk::C_TEXTURE != nullptr)
	{
		shader->activate();

		Chunk::C_TEXTURE->activate();

		delta_model_uniform->send(p_offset);
		animation_state_uniform->send(p_animation_state);
		uvs_unit_uniform->send(Chunk::C_TEXTURE->unit());
		texture_uniform->send(0);

		model_space_buffer->activate();
		model_uvs_buffer->activate();
		animation_sprite_delta_buffer->activate();
		indexes_buffer->activate();

		shader->cast(jgl::Shader::Mode::Triangle, indexes_buffer->size() / sizeof(jgl::Uint));
	}
}