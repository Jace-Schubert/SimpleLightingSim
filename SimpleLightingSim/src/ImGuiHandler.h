#pragma once
#include <GLFW/glfw3.h>
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

class ImGuiHandler 
{
public: 
    ImGuiHandler(GLFWwindow* window)
        : m_ShowDemoWindow(true), m_ShowAnotherWindow(false)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        m_IO = ImGui::GetIO(); 
        m_IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     
        m_IO.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        const char* glsl_version = "#version 130";
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    ~ImGuiHandler()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void NewFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
    void DoStuff(float* lightColor)
    {
        static float f = 0.0f;
        static int counter = 0;
        ImGui::Begin("Control Pad");                        

        ImGui::Text("Use WASD and the mouse to navigate the scene");  
        ImGui::Text("Press M to hide the cursor and lock to the center of the window");
        ImGui::Text("Press Esc to close the window");

        //ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 3.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("light color", lightColor); // Edit 3 floats representing a color

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / m_IO.Framerate, m_IO.Framerate);
        ImGui::End();
    }
    void Render()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
private:
    bool m_ShowDemoWindow;
    bool m_ShowAnotherWindow;
    ImGuiIO m_IO;
};