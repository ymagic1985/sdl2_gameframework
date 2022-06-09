#version 410 core
out vec4 FragColor; 

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

//uniform float mixValue;

void main()
{   
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // difuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 relectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, relectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 lighting = ambient + diffuse + specular;
    vec4 mixColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
    
    FragColor = vec4(mixColor.x * lighting.x, mixColor.y * lighting.y, mixColor.z * lighting.z, 1.0);
} 
