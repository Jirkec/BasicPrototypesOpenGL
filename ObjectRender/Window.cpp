
#include <stdlib.h>
#include <stdio.h>

#include "Window.h"

RenderWindow::RenderWindow() : m_resolution(defaultResolution), m_title((char*)"Render Window")
{
    memcpy_s(m_backgroundColor, sizeof(vec4), defaultBackgroundColor, sizeof(vec4));
}


RenderWindow::RenderWindow(Resolution in_res, const char* in_Title) : m_resolution(in_res), m_title((char*)in_Title)
{
    memcpy_s(m_backgroundColor, sizeof(vec4), defaultBackgroundColor, sizeof(vec4));
}

RenderWindow::~RenderWindow()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();

    if (m_renderThread.joinable())
    {
        m_renderThread.join();
    }
}

bool RenderWindow::CreateWindow()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        // Initialization failed
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_resolution.width, m_resolution.height, m_title, NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        return false;
    }

    glfwSetKeyCallback(m_window, key_callback);
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);
    glfwSetCursorPosCallback(m_window, cursor_position_callback);


    glfwMakeContextCurrent(m_window);
    gladLoadGL(glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST);

    glfwSwapInterval(1);

    SetBackgroundColor();

   //m_renderThread = std::thread(&RenderWindow::RenderLoop, this);
    RenderLoop();
    return false;
}

void RenderWindow::SetBackgroundColor(const vec4& color)
{
    memcpy_s(m_backgroundColor, sizeof(vec4), defaultBackgroundColor, sizeof(vec4));
    SetBackgroundColor();
}

void RenderWindow::SetBackgroundColor()
{
    glClearColor(m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], m_backgroundColor[3]);
}

void RenderWindow::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void RenderWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void RenderWindow::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Store for use in picking code
        printf("Mouse Click at: %f, %f\n", xpos, ypos);
    }
    
    //if (button == GLFW_MOUSE_BUTTON_RIGHT) {
    //    if (action == GLFW_PRESS) {
    //        rightMouseDown = true;
    //        firstMouse = true; // Reset for smooth movement
    //    }
    //    else if (action == GLFW_RELEASE) {
    //        rightMouseDown = false;
    //    }
    //}
}

void RenderWindow::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
}

void RenderWindow::RenderLoop()
{
    while (!glfwWindowShouldClose(m_window))
    {
        // 1. Poll/input events
        glfwPollEvents();

        int width, height;
        glfwGetFramebufferSize(m_window, &width, &height);
        const float ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(m_window);
    }
}
