#version 330 core

in vec2 UV;

layout(location = 0) out vec4 color;

uniform sampler2D textureID;

void main()
{
	if (UV.x < 0 || UV.x > 1 || UV.y < 0 || UV.y > 1)
	{
		color = vec4(1, 0, 0, 1);
	}
	else
	{
		color = texture(textureID, UV).rgba;

		if (color.a == 0)
			discard;
	}
}