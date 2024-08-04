#pragma once
#include <string>
#include "vendor/glm/gtc/type_ptr.hpp"

struct ShaderProgramSource 
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();
	void Bind();
	void Unbind();
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, std::string shaderSource);
	void SetUniform1i(const std::string& name, int v0);
	void SetUniform1f(const std::string& name, float v0);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform3f(const std::string& name, glm::vec3 vec);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4(const std::string& name, glm::mat4 transform);
private:
	unsigned int m_RendererID;
	const std::string& m_Filepath;
};