#include "Shader.h"

Shader::Shader(std::string& vertFilepath, std::string& fragFilepath)
{
	std::string vertSource = ParseShader(vertFilepath);
	std::string fragSource = ParseShader(fragFilepath);

	id = CreateShaderProgram(vertSource, fragSource);
	if (!id)
		std::cout << "ERROR: COULD NOT CREATE SHADER PROGRAM." << std::endl;
}

std::string Shader::ParseShader(const std::string& filepath)
{

	std::ifstream stream(filepath);

	std::string line;
	std::stringstream ss;

	while (getline(stream, line))
	{
		ss << line << '\n';
	}
	return ss.str();
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{

	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//Error checker, returns false if contains syntax errors
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{

		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile shader of type " << type << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}
	else
	{
		std::cout << "Shader of type " << type << " compiled successfully." << std::endl;
	}

	return id;
}

unsigned int Shader::CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{

	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	
	if (vs && fs)
	{
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}
	else
		return 0;
}

void Shader::Use()
{
	glUseProgram(id);
}

void Shader::Delete()
{
	glDeleteProgram(id);
}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::SetMat3(const std::string& name, glm::mat3 value) const
{
	glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat4(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetVec2(const std::string& name, GLfloat v0, GLfloat v1) const
{
	glUniform2f(glGetUniformLocation(id, name.c_str()), v0, v1);
}

void Shader::SetVec2(const std::string& name, glm::vec2 v) const
{
	glUniform2f(glGetUniformLocation(id, name.c_str()), v.x, v.y);
}

void Shader::SetVec3(const std::string & name, GLfloat v0, GLfloat v1, GLfloat v2) const
{
	glUniform3f(glGetUniformLocation(id, name.c_str()), v0, v1, v2);
}

void Shader::SetVec3(const std::string& name, glm::vec3 v) const
{
	glUniform3f(glGetUniformLocation(id, name.c_str()), v.x, v.y, v.z);
}

void Shader::SetVec4(const std::string & name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const
{
	glUniform4f(glGetUniformLocation(id, name.c_str()), v0, v1, v2, v3);
}

void Shader::SetVec4(const std::string& name, glm::vec4 v) const
{
	glUniform4f(glGetUniformLocation(id, name.c_str()), v.x, v.y, v.z, v.a);
}
