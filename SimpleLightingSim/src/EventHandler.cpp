#include "EventHandler.h"
#include "Camera.h"

extern Camera g_Cam;

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, 800, 600);
}

void MouseCallback(GLFWwindow* window, double mouseX, double mouseY)
{
    static float lastX{ (float)mouseX }, lastY{ (float)mouseY };
    float offsetX{ (float)mouseX - lastX };
    float offsetY{ lastY - (float)mouseY };
    lastX = (float)mouseX;
    lastY = (float)mouseY;
    const float sensitivity = 0.1f;
    offsetX *= sensitivity;
    offsetY *= sensitivity;
    g_Cam.Rotate(offsetY, offsetX);
}

void ScrollCallback(GLFWwindow* window, double offsetX, double offsetY)
{
    g_Cam.SetZoom(g_Cam.GetZoom() - (float)offsetY);
}

EventHandler::EventHandler()
    : m_window(nullptr)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(640, 480, "Game", NULL, NULL);

    if (!m_window)
    {
        glfwTerminate();
    }

    glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
    glfwSetCursorPosCallback(m_window, MouseCallback);
    glfwSetScrollCallback(m_window, ScrollCallback);

    glfwMakeContextCurrent(m_window);
}

EventHandler::~EventHandler()
{
    glfwTerminate();
}

bool EventHandler::ShouldClose()
{
    return (bool)glfwWindowShouldClose(m_window);
}

void EventHandler::SwapBuffers()
{
    glfwSwapBuffers(m_window);
}

void EventHandler::ProcessInput(float deltaTime)
{
    glfwPollEvents();
    static bool cursorEnabled = true;
    g_Cam.SetSpeed(deltaTime * 2.5f);

    if (glfwGetKey(m_window, GLFW_KEY_M) == GLFW_PRESS) 
    {     
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL + 2 * cursorEnabled);  
        cursorEnabled = cursorEnabled ^ 1;
    }   
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, 1);
    }
    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    {
        g_Cam.SetPos(g_Cam.GetPos() + g_Cam.GetForwardVec() * g_Cam.GetSpeed());
    }
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
    {
        g_Cam.SetPos(g_Cam.GetPos() - g_Cam.GetForwardVec() * g_Cam.GetSpeed());
    }
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        g_Cam.SetPos(g_Cam.GetPos() - glm::normalize(glm::cross(g_Cam.GetForwardVec(), g_Cam.GetUpVec())) * g_Cam.GetSpeed());
    }
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        g_Cam.SetPos(g_Cam.GetPos() + glm::normalize(glm::cross(g_Cam.GetForwardVec(), g_Cam.GetUpVec())) * g_Cam.GetSpeed());
    }
}

float EventHandler::GetTime()
{
    return (float)glfwGetTime();
}

GLFWwindow* EventHandler::GetWindowPointer()
{
    return m_window;
}
