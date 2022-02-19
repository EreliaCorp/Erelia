#version 330 core

in vec2 UV;
in vec2 deltaUV;

layout(location = 0) out vec4 color;

uniform sampler2D textureID;

void main()
{
	vec2 tmp_uv = deltaUV + UV;
	
	if (tmp_uv.x < 0 || tmp_uv.x > 1 || tmp_uv.y < 0 || tmp_uv.y > 1)
		discard;

	color = texture(textureID, tmp_uv).rgba;

	if (color.a == 0)
		discard;
}