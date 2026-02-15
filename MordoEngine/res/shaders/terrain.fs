#version 330 core
in vec2 TexCoord;
in float Height;
in vec3 Normal;
in vec3 WorldPos;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform float heightThreshold1;
uniform float heightThreshold2;
uniform vec3 lightDir;

void main()
{
    // Ya viene escalado del vertex shader
    vec3 grassColor = texture(texture1, TexCoord).rgb;
    vec3 dirtColor = texture(texture2, TexCoord).rgb;
    vec3 rockColor = texture(texture3, TexCoord).rgb;
    
    vec3 color;
    if (Height < heightThreshold1) {
        color = grassColor;
    } else if (Height < heightThreshold2) {
        float blend = (Height - heightThreshold1) / (heightThreshold2 - heightThreshold1);
        color = mix(grassColor, dirtColor, blend);
    } else {
        float blend = smoothstep(heightThreshold2, heightThreshold2 + 0.1, Height);
        color = mix(dirtColor, rockColor, blend);
    }
    
    vec3 norm = normalize(Normal);
    vec3 light = normalize(lightDir);
    float diff = max(dot(norm, light), 0.0);
    
    vec3 ambient = 0.3 * color;
    vec3 diffuse = 0.7 * diff * color;
    
    FragColor = vec4(ambient + diffuse, 1.0);
}