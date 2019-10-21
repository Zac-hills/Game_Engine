#version 460

const vec2 quadVertices[6] = { vec2(-1.0, -1.0), vec2(1.0, -1.0), vec2(-1.0, 1.0), vec2(1.0, 1.0), vec2(-1.0,1.0), vec2(1.0,-1.0) };
const vec2 quadUV[6] = {vec2(0,0), vec2(1,0), vec2(0,1), vec2(1,1), vec2(0,1), vec2(1,0)};

out vec2 textureUV;

void main()
{
    gl_Position = vec4(quadVertices[gl_VertexID], 0.0, 1.0);
    textureUV = quadUV[gl_VertexID];
}