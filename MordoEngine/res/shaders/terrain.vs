#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in float aHeight;

out vec2 TexCoord;
out float Height;

uniform mat4 projection;
uniform mat4 view;
uniform float textureScale;

void main()
{
    gl_Position = projection * view * vec4(aPos, 1.0);
    
    // Repetir texturas multiplicando las coordenadas UV
    TexCoord = aTexCoord * textureScale;
    
    // Pasar altura normalizada al fragment shader
    Height = aHeight;
}