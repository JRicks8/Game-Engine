#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

#include "Shader.h"

struct PointLight
{
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	unsigned int slot;
};

struct DirLight
{
	glm::vec3 direction;
	
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

void SendLightInfo(PointLight light, Shader& shader)
{
	shader.SetVec3("pointLights[" + std::to_string(light.slot) + "].position", light.position);
	shader.SetVec3("pointLights[" + std::to_string(light.slot) + "].ambient", light.ambient);
	shader.SetVec3("pointLights[" + std::to_string(light.slot) + "].diffuse", light.diffuse);
	shader.SetVec3("pointLights[" + std::to_string(light.slot) + "].specular", light.specular);
	shader.SetFloat("pointLights[" + std::to_string(light.slot) + "].constant", light.constant);
	shader.SetFloat("pointLights[" + std::to_string(light.slot) + "].linear", light.linear);
	shader.SetFloat("pointLights[" + std::to_string(light.slot) + "].quadratic", light.quadratic);
}

void SendLightInfo(DirLight light, Shader& shader)
{
	shader.SetVec3("dirLight.direction", light.direction);
	shader.SetVec3("dirLight.ambient", light.ambient);
	shader.SetVec3("dirLight.diffuse", light.diffuse);
	shader.SetVec3("dirLight.specular", light.specular);
}

#endif