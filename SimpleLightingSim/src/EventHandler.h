#pragma once
#include <GLFW/glfw3.h>

class EventHandler 
{
public:
    EventHandler();
    ~EventHandler();
    bool ShouldClose();
    void SwapBuffers();
    void ProcessInput(float deltaTime);
    float GetTime();
    GLFWwindow* GetWindowPointer();
private:
    GLFWwindow* m_window;
};



