#version 460

uniform vec4 Vertices[6];

uniform vec2 UV[6];

uniform vec3 Color;

uniform mat4 ViewProjection;

uniform mat4 Model;

out vec2 UVCoordinates;

out vec3 FlatColor;

void main()
{
	gl_Position = ViewProjection * Model * Vertices[gl_VertexID];
	UVCoordinates = UV[gl_VertexID];
	FlatColor = Color;
}