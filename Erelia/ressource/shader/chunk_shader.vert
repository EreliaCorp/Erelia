#version 330 core

layout(location = 0) in vec3 model_space;
layout(location = 1) in vec2 model_uvs;
layout(location = 2) in float animation_sprite_delta;

uniform vec3 delta_model;
uniform int animation_state;
uniform vec2 uvs_unit;

out vec2 UV;

void main()
{
	gl_Position = vec4(model_space + delta_model, 1.0f);

	UV = model_uvs + (vec2(animation_state * animation_sprite_delta, 0) * uvs_unit);
}