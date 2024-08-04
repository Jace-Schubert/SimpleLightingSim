#include "Renderer.h"
#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>

Renderer::Renderer()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to load GLAD";
    }
    glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{

}

void Renderer::Draw(int count)
{
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}

void Renderer::SetClearColor(float v0, float v1, float v2)
{    
    glClearColor(v0, v1, v2, 1.0f);
}

void Renderer::SetClearColor(glm::vec3 color)
{
    SetClearColor(color.x, color.y, color.z);
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}