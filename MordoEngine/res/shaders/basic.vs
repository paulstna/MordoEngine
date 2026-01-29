#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform vec3 iPos;
uniform float iSize;

out vec2 TexCoord;

void main()
{
    vec3 pos = aPos * iSize + iPos;
    gl_Position = vec4(pos, 1.0);
    TexCoord = aTexCoord;
}
