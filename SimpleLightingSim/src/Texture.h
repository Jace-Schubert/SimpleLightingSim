#pragma once
#include <string>

typedef unsigned int GLuint;

class Texture
{
public:
	Texture(const std::string& filepath);
	~Texture();
	void Bind();
	void Unbind();
private:
	unsigned int m_RendererID;
	const std::string m_Filepath;
	static unsigned int m_ActiveTexturesCount;
};