#ifndef SHADER_H
#define SHADER_H

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	unsigned int id;

	Shader(std::string& vertFilepath, std::string& fragFilepath);

	std::string ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);

	void Use();
	void Delete();

	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetMat3(const std::string& name, glm::mat3 value) const;
	void SetMat4(const std::string& name, glm::mat4 value) const;
	void SetVec2(const std::string& name, GLfloat v0, GLfloat v1) const;
	void SetVec2(const std::string& name, glm::vec2 v) const;
	void SetVec3(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2) const;
	void SetVec3(const std::string& name, glm::vec3 v) const;
	void SetVec4(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const;
	void SetVec4(const std::string& name, glm::vec4 v) const;
};

#endif