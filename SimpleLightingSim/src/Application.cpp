#include "EventHandler.h"
#include "ImGuiHandler.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Data.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

Camera g_Cam(glm::vec3(0.0f, 0.0f, 3.0f));

int main()
{
    // Initializes GLFW, IMGUI, and GLAD
    EventHandler eventHandler;                                  
    ImGuiHandler imGuiHandler(eventHandler.GetWindowPointer());
    Renderer renderer;

    // Sets background color
    glm::vec3 clearColor(0.0f);
    renderer.SetClearColor(clearColor);

    // Creates buffers and fills them with generic cube data found in data.h
    VertexArray woodContainerVA;
    VertexBuffer woodConatinerVB(vertices, sizeof(vertices));   
    IndexBuffer woodContainerIB(indicies ,sizeof(indicies));

    woodContainerVA.AddAttrib(3, GL_FLOAT, GL_FALSE); // Positions 
    woodContainerVA.AddAttrib(3, GL_FLOAT, GL_FALSE); // Normals
    woodContainerVA.AddAttrib(2, GL_FLOAT, GL_FALSE); // Texture Coords
    woodContainerVA.EnableAttribs();

    VertexArray lightVA;
    VertexBuffer lightVB(vertices, sizeof(vertices));
    IndexBuffer lightIB(indicies, sizeof(indicies));

    lightVA.AddAttrib(3, GL_FLOAT, GL_FALSE); // Positions
    lightVA.SetStride(lightVA.GetStride() + 5 * sizeof(float)); // Accounts for unused Normals and Texture coords
    lightVA.EnableAttribs();

    // Parses shaders and creates programs
    Shader genericShader("res/shaders/GenericShader.txt");
    Shader lightSourceShader("res/shaders/LightSourceShader.txt");
    
    // Activates Textures and generates mipmaps
    Texture woodContainer("res/textures/wood_container.png");
    Texture woodContainerSpecular("res/textures/wood_container(specular_map).png");

    // Initalizes model positions
    glm::mat4 iMAT(1.0f); 
    glm::mat4 woodContainerModel(1.0f);
    glm::mat4 lightModel(1.0f);
    glm::vec3 lightPos(0.0f, 0.0f, -3.0f);

    float lightColorArray[3] = { 1.0f, 1.0f, 1.0f };
    float lastFrame{ 0.0f };

    while (!eventHandler.ShouldClose())
    {       
        renderer.Clear();
        imGuiHandler.NewFrame();

        // Position calculations
        lightModel = glm::translate(iMAT, lightPos);
        glm::mat4 proj = glm::perspective(glm::radians(g_Cam.GetZoom()), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(g_Cam.GetPos(), g_Cam.GetForwardVec() + g_Cam.GetPos(), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 woodContainerMVP = proj * view * woodContainerModel;
        glm::mat4 lightMVP = proj * view * lightModel;

        // Draw wood container
        glm::vec3 lightColor = glm::vec3(lightColorArray[0], lightColorArray[1], lightColorArray[2]);
        genericShader.Bind();
        genericShader.SetUniformMat4("u_Matrix", woodContainerMVP);
        genericShader.SetUniform3f("u_ObjectColor", 1.0f, 0.5f, 0.31f);
        genericShader.SetUniform3f("u_LightColor", lightColor);
        genericShader.SetUniform3f("u_Light.pos", lightPos);
        genericShader.SetUniform3f("u_Light.ambient", glm::vec3(0.2f) * lightColor);
        genericShader.SetUniform3f("u_Light.diffuse", glm::vec3(0.5f) * lightColor);
        genericShader.SetUniform3f("u_Light.specular", glm::vec3(1.0f) * lightColor);
        genericShader.SetUniform3f("u_ViewPos", g_Cam.GetPos());
        genericShader.SetUniform1i("u_Material.diffuse", 0);
        genericShader.SetUniform1i("u_Material.specular", 1);
        genericShader.SetUniform1f("u_Material.shininess", 32.0f);
        woodContainerVA.Bind();
        renderer.Draw(sizeof(indicies) / sizeof(unsigned int));
        
        // Draw light source
        lightSourceShader.Bind();
        lightSourceShader.SetUniformMat4("u_Matrix", lightMVP);
        lightSourceShader.SetUniform3f("u_Color", lightColor);
        lightVA.Bind();
        renderer.Draw(sizeof(indicies) / sizeof(unsigned int));

        // IMGUI windowing
        imGuiHandler.DoStuff(lightColorArray);
        imGuiHandler.Render();

        // Swaps front and back buffers
        eventHandler.SwapBuffers();       

        // Input Processing and time calculations
        float time = eventHandler.GetTime();
        float deltaTime = time - lastFrame;
        lastFrame = time;
        eventHandler.ProcessInput(deltaTime);

        lightPos = glm::vec3(sin(glm::radians(time * 10.0f)) * 3.0f, 0.0f, cos(glm::radians(time * 10.0f)) * -3.0f);
    }
    return 0;
}