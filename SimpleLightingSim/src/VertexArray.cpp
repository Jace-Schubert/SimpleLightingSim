#include "VertexArray.h"
#include <glad/glad.h>

VertexArray::VertexArray()
	: m_RendererID(0), m_Stride(0)
{
	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

VertexArray::~VertexArray()
{

}

void VertexArray::Bind()
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::AddAttrib(unsigned int count, unsigned int type, bool normalize)
{
	m_Layouts.push_back({ count, type, normalize });
	m_Stride += count * sizeof(type);
}

void VertexArray::EnableAttribs()
{
	long long offset = 0;
	for (int i = 0; i < (int)m_Layouts.size(); i++)
	{
		VertexAttribLayout layout = m_Layouts[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, layout.count, layout.type, layout.normalize, m_Stride, (void*)offset);
		offset += layout.count * sizeof(layout.type);
	}
}

void VertexArray::SetStride(const unsigned int& stride)
{
	m_Stride = stride;
}

unsigned int VertexArray::GetStride()
{
	return m_Stride;
}