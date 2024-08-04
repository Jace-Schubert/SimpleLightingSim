#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

Shader::Shader(const std::string& filepath)
	: m_RendererID(0), m_Filepath(filepath)
{
    ShaderProgramSource src = ParseShader(filepath);
    unsigned int vertexID = CompileShader(GL_VERTEX_SHADER, src.VertexSource);
    unsigned int fragmentID = CompileShader(GL_FRAGMENT_SHADER, src.FragmentSource);
    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, vertexID);
    glAttachShader(m_RendererID, fragmentID);
    glLinkProgram(m_RendererID);
    glValidateProgram(m_RendererID);
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}
Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}
void Shader::Bind()
{
    glUseProgram(m_RendererID);
}
void Shader::Unbind()
{
    glUseProgram(0);
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath) 
{
    std::ifstream stream(filepath);
    enum class ShaderType 
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    ShaderType type = ShaderType::NONE;
    std::string line;
    std::stringstream ss[2];
    while (getline(stream, line)) 
    {
        if (line.find("#shader") != std::string::npos) 
        {
            if (line.find("vertex") != std::string::npos) 
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) 
            {
                type = ShaderType::FRAGMENT;

            }
        }
        else if (type != ShaderType::NONE) {
            ss[(int)type] << line << "\n";
        }
    }
    return { ss[0].str(), ss[1].str() };

}

unsigned int Shader::CompileShader(unsigned int type, std::string shaderSource)
{
    unsigned int id = glCreateShader(type);
    const char* src = shaderSource.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) 
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)_malloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader")
            << "\n" << message << "\n";
        glDeleteShader(id);
        return 0;
    }
    return id;
}

void Shader::SetUniform1i(const std::string& name, int v0)
{
    int uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform1i(uniformLocation, v0);
}

void Shader::SetUniform1f(const std::string& name, float v0)
{
    int uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform1f(uniformLocation, v0);
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
    int uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform3f(uniformLocation, v0, v1, v2);
}

void Shader::SetUniform3f(const std::string& name, glm::vec3 vec)
{
    SetUniform3f(name, vec.x, vec.y, vec.z);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    int uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform4f(uniformLocation, v0, v1, v2, v3);
}

void Shader::SetUniformMat4(const std::string& name, glm::mat4 transform)
{
    int uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(transform));
}