#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in float Height;

out vec4 FragColor;

uniform sampler2D texture1; 
uniform sampler2D texture2; 
uniform sampler2D texture3; 

uniform float heightThreshold1; 
uniform float heightThreshold2; 
uniform vec3 reverseLightDir;

vec4 CalculateTexColor()
{
    vec3 color1 = texture(texture1, TexCoord).rgb;
    vec3 color2 = texture(texture2, TexCoord).rgb;
    vec3 color3 = texture(texture3, TexCoord).rgb;
   
    float blendWidth = 0.15;
    float blend1to2 = smoothstep(heightThreshold1 - blendWidth, 
                                 heightThreshold1 + blendWidth, 
                                 Height);
    float blend2to3 = smoothstep(heightThreshold2 - blendWidth, 
                                 heightThreshold2 + blendWidth, 
                                 Height);
    
    vec3 finalColor = mix(color1, color2, blend1to2);
    finalColor = mix(finalColor, color3, blend2to3);
    return vec4(finalColor, 1.0f);
}


void main()
{
    vec4 TexColor = CalculateTexColor();
    vec3 Normal_ = normalize(Normal);
    float Diffuse = dot(Normal_, reverseLightDir);
    Diffuse = max(0.3f, Diffuse);
    FragColor = TexColor * Diffuse;
}