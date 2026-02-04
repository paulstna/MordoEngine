#version 330 core

in vec2 TexCoord;
in float Height;

out vec4 FragColor;

uniform sampler2D texture1; // Textura baja (arena, pasto bajo)
uniform sampler2D texture2; // Textura media (pasto, tierra)
uniform sampler2D texture3; // Textura alta (roca, nieve)

uniform float heightThreshold1; // Transición tex1->tex2 (ej: 0.3)
uniform float heightThreshold2; // Transición tex2->tex3 (ej: 0.7)

void main()
{
    // Muestrear las 3 texturas
    vec3 color1 = texture(texture1, TexCoord).rgb;
    vec3 color2 = texture(texture2, TexCoord).rgb;
    vec3 color3 = texture(texture3, TexCoord).rgb;
    
    // Calcular pesos de mezcla con transiciones suaves
    float blendWidth = 0.15; // Ancho de la transición
    float blend1to2 = smoothstep(heightThreshold1 - blendWidth, 
                                 heightThreshold1 + blendWidth, 
                                 Height);
    float blend2to3 = smoothstep(heightThreshold2 - blendWidth, 
                                 heightThreshold2 + blendWidth, 
                                 Height);
    
    // Mezclar texturas progresivamente
    vec3 finalColor = mix(color1, color2, blend1to2);
    finalColor = mix(finalColor, color3, blend2to3);
    
    FragColor = vec4(finalColor, 1.0);
}