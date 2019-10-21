#version 460

uniform sampler2D tex;

in vec2 textureUV;

out vec4 outColor;

void main()
{
	outColor = texture(tex, textureUV).rgba;
}