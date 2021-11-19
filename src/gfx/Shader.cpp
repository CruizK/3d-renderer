#include "Shader.h"
#include "core/Log.h"

#include <iostream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

Shader::Shader()
	: m_ProgramID(0), m_VertexShaderID(0), m_FragmentShaderID(0)
{
}

Shader::~Shader()
{
	glDeleteProgram(m_ProgramID);
}

void Shader::CreateFromFile(const std::string &path)
{
	ShaderSrc src;
	ReadShaderFromFile(path, src);
	CreateFromMemory(src);
}

void Shader::CreateFromMemory(const ShaderSrc &src)
{
	m_VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	const char *vs = src.vertSrc.c_str();

	glShaderSource(m_VertexShaderID, 1, &vs, NULL);
	glCompileShader(m_VertexShaderID);

	int success;
	char infoLog[512];
	glGetShaderiv(m_VertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_VertexShaderID, 512, NULL, infoLog);
		CORE_ERROR("VERT SHADER COMPILATION ERROR: {0}", infoLog);
		return;
	}

	m_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const char *fs = src.fragSrc.c_str();

	glShaderSource(m_FragmentShaderID, 1, &fs, NULL);
	glCompileShader(m_FragmentShaderID);

	glGetShaderiv(m_FragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_FragmentShaderID, 512, NULL, infoLog);
		CORE_ERROR("FRAGMENT SHADER COMPILATION ERROR: {0}", infoLog);
		return;
	}

	m_ProgramID = glCreateProgram();

	glAttachShader(m_ProgramID, m_VertexShaderID);
	glAttachShader(m_ProgramID, m_FragmentShaderID);
	glLinkProgram(m_ProgramID);

	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ProgramID, 512, NULL, infoLog);
		CORE_ERROR("SHADER PROGRAM LINKING ERROR: {0}", infoLog);
		return;
	}

	glDeleteShader(m_VertexShaderID);
	glDeleteShader(m_FragmentShaderID);

	CORE_TRACE("SHADER CREATED");
}

void Shader::ReadShaderFromFile(const std::string &path, ShaderSrc &src)
{
	std::fstream file;
	std::string fileSrc;
	file.open(path);
	if (file.is_open())
	{
		std::string line;

		while (std::getline(file, line))
		{
			fileSrc += line + '\n';
		}
	}
	else
	{
		CORE_ERROR("SHADER NOT FOUND AT PATH: {0}", path);
		return;
	}

	size_t vertStart = fileSrc.rfind("#vertex");
	size_t fragStart = fileSrc.rfind("#fragment");

	if (vertStart < fragStart)
	{
		src.vertSrc = fileSrc.substr(vertStart + 7, fragStart - 7);
		src.fragSrc = fileSrc.substr(fragStart + 9);
	}
	else
	{
		src.fragSrc = fileSrc.substr(fragStart + 9, vertStart - 9);
		src.vertSrc = fileSrc.substr(vertStart + 7);
	}
}

void Shader::Use() const
{
	glUseProgram(m_ProgramID);
}

u32 Shader::GetUniformLocation(const std::string &name)
{
	auto found = m_UniformLocations.find(name);

	if (found != m_UniformLocations.end())
		return found->second;

	int location = glGetUniformLocation(m_ProgramID, name.c_str());

	if (location == -1)
	{
		CORE_ERROR("UNIFORM NOT FOUND: {0}", name);
		return m_UniformLocations.begin()->second;
	}

	m_UniformLocations[name] = location;
	return location;
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &value)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetFloat1v(const std::string &name, u32 count, float *value)
{
	glUniform1fv(GetUniformLocation(name), count, value);
}

void Shader::SetInt(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetInt1v(const std::string &name, u32 count, int *value)
{
	glUniform1iv(GetUniformLocation(name), count, value);
}

void Shader::SetFloat(const std::string &name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetVec2(const std::string &name, const glm::vec2 &value)
{
	glUniform2f(GetUniformLocation(name), value.x, value.y);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &value)
{
	glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}