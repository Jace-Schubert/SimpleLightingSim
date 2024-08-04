#pragma once
#include <vector>

typedef unsigned int GLenum;

struct VertexAttribLayout
{
	unsigned int count;
	unsigned int type;
	bool normalize;
};

class VertexArray 
{
public:
	VertexArray();
	~VertexArray();
	void Bind();
	void Unbind();
	void AddAttrib(unsigned int count, unsigned int type, bool normalize);
	void EnableAttribs();
	void SetStride(const unsigned int& stride);
	unsigned int GetStride();
private:
	unsigned int m_RendererID;
	unsigned int m_Stride;
	std::vector<VertexAttribLayout> m_Layouts;
};