#version 330 core

layout(location = 0) in vec3 model_space;
layout(location = 1) in vec2 model_uvs;

uniform vec3 delta_model;
uniform vec2 model_size;
uniform vec2 delta_uvs;

out vec2 UV;
out vec2 deltaUV;

void main()
{
	gl_Position = vec4(model_space * vec3(model_size, 1) + delta_model, 1.0f);
	
	UV = model_uvs;
	deltaUV = delta_uvs;
}