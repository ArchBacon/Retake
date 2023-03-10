#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoords;
in vec3 normal;
in vec3 currentPos;

uniform sampler2D albedoMap;
uniform sampler2D specularMap;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
    // ambient lighting
    float ambient = 0.20f;
    
    // diffuse lighting
    vec3 normalized = normalize(normal);
    vec3 lightDirection = normalize(lightPos - currentPos);
    float diffuse = max(dot(normalized, lightDirection), 0.0f);
    
    // specular lighting
    float specularLight = 0.50f;
    vec3 viewDirection = normalize(camPos - currentPos);
    vec3 reflectionDirection = reflect(-lightDirection, normalized);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8.0f);
    float specular = specAmount * specularLight;
    
    FragColor = (texture(albedoMap, texCoords) * (diffuse + ambient) + texture(specularMap, texCoords).r * specular) * lightColor;
}
