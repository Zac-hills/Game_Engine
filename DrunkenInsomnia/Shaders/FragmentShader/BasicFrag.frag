#version 460

in vec2 UVCoordinates;

in vec3 FlatColor;

out vec4 OutColor;

void main()
{
	OutColor = vec4(FlatColor, 1.0f);
}