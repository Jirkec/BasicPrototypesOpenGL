#pragma once

#include <filesystem>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "linmath.h"
#include <thread>
#include "RenderObject.h"

struct Resolution
{
    int width;
    int height;
};

const Resolution defaultResolution = { 800, 600 };
const vec4 defaultBackgroundColor = { 0.67f, 0.82f, 0.93f, 1.0f };

class RenderWindow 
{

public:
    RenderWindow();
    RenderWindow(Resolution in_res, const char* in_Title = "Render Window");
    ~RenderWindow();

    bool CreateWindow();
    void SetBackgroundColor(const vec4& color);
    void SetBackgroundColor();

    void AddObject(RenderObject& object);
    void RemoveObject(RenderObject& object);
    const std::vector<RenderObject*>& GetRenderObjects() const { return m_renderObjects; }



private:
    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

    void RenderLoop();

public:
private:
    Resolution m_resolution = defaultResolution;
    GLFWwindow* m_window = nullptr;
    char* m_title;
    vec4 m_backgroundColor;
    std::thread m_renderThread;
    std::vector<RenderObject*> m_renderObjects;
};