#include "Texture.h"
#include <iostream>
#include <glad/glad.h>
#include "vendor/stb_image.h"

unsigned int Texture::m_ActiveTexturesCount = 0;
Texture::Texture(const std::string& filepath)
	: m_RendererID(0), m_Filepath(filepath)
{
	stbi_set_flip_vertically_on_load(1);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 4);
	if (!data) { std::cout << "uh oh"; }
	glGenTextures(1, &m_RendererID);
	glActiveTexture(GL_TEXTURE0 + m_ActiveTexturesCount);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	m_ActiveTexturesCount++;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}

Texture::~Texture()
{

}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}