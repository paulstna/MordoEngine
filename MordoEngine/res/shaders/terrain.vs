#version 330 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;
layout(location = 3) in float a_Height;

out vec2 TexCoord;
out float Height;
out vec3 Normal;

uniform mat4 projection;
uniform mat4 view;
uniform float textureScale;

void main()
{
    gl_Position = projection * view * vec4(a_Pos, 1.0);
    TexCoord = a_TexCoord * textureScale;
    Normal = a_Normal;
    Height = a_Height;
}