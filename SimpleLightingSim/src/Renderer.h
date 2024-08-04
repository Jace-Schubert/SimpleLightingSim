#pragma once
#include "vendor/glm/glm.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();
	void Draw(int count);
	void SetClearColor(float v0, float v1, float v2);
	void SetClearColor(glm::vec3 color);
	void Clear();
private:

};