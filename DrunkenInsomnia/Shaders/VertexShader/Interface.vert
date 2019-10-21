#version 460

uniform vec2 Vertices[6];

uniform vec2 UVCoordinates[6];

out vec2 textureUV;

void main()
{
	textureUV = UVCoordinates[gl_VertexID];
	gl_Position = vec4(Vertices[gl_VertexID], 0.0, 1.0);
}