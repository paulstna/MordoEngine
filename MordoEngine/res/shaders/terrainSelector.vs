#version 330 core

layout(location = 0) in vec2 a_Pos;
layout(location = 1) in float a_Height;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{
    vec3 finalPosition = vec3(a_Pos.x, a_Height, a_Pos.y);
    gl_Position = projection * view * model * vec4(finalPosition,1.0);
}