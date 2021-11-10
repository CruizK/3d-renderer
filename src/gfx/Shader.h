#pragma once

#include "core/Core.h"

#include <unordered_map>
#include <string>
#include <glm/glm.hpp>

struct ShaderSrc
{
	std::string vertSrc;
	std::string fragSrc;
};

class Shader
{
public:
	Shader();
	~Shader();

	void CreateFromFile(const std::string &path);
	void CreateFromMemory(const ShaderSrc &src);

	void Use() const;

	void SetMat4(const std::string &name, const glm::mat4 &value);
	void SetFloat1v(const std::string &name, u32 count, float *value);
	void SetInt1v(const std::string &name, u32 count, int *value);
	void SetFloat(const std::string &name, float value);
	void SetVec2(const std::string &name, const glm::vec2 &value);
	void SetVec3(const std::string &name, const glm::vec3 &value);

private:
	void ReadShaderFromFile(const std::string &path, ShaderSrc &src);
	u32 GetUniformLocation(const std::string &name);

	std::unordered_map<std::string, u32> m_UniformLocations;

	u32 m_ProgramID, m_VertexShaderID, m_FragmentShaderID;
};