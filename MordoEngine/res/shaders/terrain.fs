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
uniform vec3 viewPos;

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
};
uniform DirLight dirLight;

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;      
    float constant;
    float linear;
    float quadratic;
};

uniform PointLight pointLight;


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 color)
{
    vec3 lightDir = normalize(-light.direction);
    float diff    = max(dot(normal, lightDir), 0.0);
    vec3 ambient  = light.ambient * color;
    vec3 diffuse  = light.diffuse * diff * color;
    return ambient + diffuse;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 color)
{
    vec3 lightVec  = light.position - fragPos;
    vec3 lightDir  = normalize(lightVec);
    float dist     = length(lightVec);
    float diff     = max(dot(normal, lightDir), 0.0);

    vec3 viewDir    = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec      = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    float attenuation = 1.0 / (light.constant
                              + light.linear    * dist
                              + light.quadratic * dist * dist);

    vec3 ambient  = light.ambient  * color        * attenuation;
    vec3 diffuse  = light.diffuse  * diff * color * attenuation;
    vec3 specular = light.specular * spec * attenuation;

    return ambient + diffuse + specular;
}


void main()
{
    vec3 grassColor = texture(texture1, TexCoord).rgb;
    vec3 dirtColor  = texture(texture2, TexCoord).rgb;
    vec3 rockColor  = texture(texture3, TexCoord).rgb;

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

    vec3 result = CalcDirLight(dirLight, norm, color);
    result     += CalcPointLight(pointLight, norm, WorldPos, color);

    FragColor = vec4(result, 1.0);
}