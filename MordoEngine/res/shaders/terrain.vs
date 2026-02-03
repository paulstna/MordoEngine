#version 330 core
layout (location = 0) in vec3 a_Pos;

uniform mat4 view;
uniform mat4 projection;
uniform float heightScale;

out vec4 Color;

void main()
{
    gl_Position = projection * view * vec4(a_Pos, 1.0);

    float h = a_Pos.y / heightScale;
    h = clamp(h * 0.85 + 0.15, 0.0, 1.0);
    Color = vec4(vec3(h), 1.0);
}
