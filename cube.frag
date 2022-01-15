#version 330 core

struct Material {
    sampler2D texture_diffuse0;
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_specular0;
    sampler2D texture_specular1;
    float shininess;
}; 

struct DirLight {
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};
#define NR_POINT_LIGHTS 4

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];

float near = 0.1;
float far = 1000.0;

vec3 CalculateDirectionalLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{	
	vec3 finalLight = vec3(0.0);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 normal = normalize(Normal);
	
	finalLight += CalculateDirectionalLight(dirLight, normal, viewDir);
	
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
		finalLight += CalculatePointLight(pointLights[i], normal, FragPos, viewDir);
	
	FragColor = vec4(finalLight, 1.0);
	
	// depth channel
	//float z = gl_FragCoord.z * 2.0 - 1.0;
	//float val = (2.0 * near * far) / (far + near - z * (far - near));
	//float depth = val / far;
	//FragColor = vec4(vec3(depth), 1.0);
}

vec3 CalculateDirectionalLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	// diffuse
	float diff = max(dot(normal, lightDir), 0.0);
	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	// combine
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse0, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse0, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular0, TexCoords));
	return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.texture_diffuse0, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.texture_diffuse0, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular0, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
	// make sure that when receiving no values (no light) we don't send negative values
	ambient = vec3(max(ambient.x, 0.0), max(ambient.y, 0.0), max(ambient.z, 0.0));
	diffuse = vec3(max(diffuse.x, 0.0), max(diffuse.y, 0.0), max(diffuse.z, 0.0));
	specular = vec3(max(specular.x, 0.0), max(specular.y, 0.0), max(specular.z, 0.0));
    return (ambient + diffuse + specular);
}