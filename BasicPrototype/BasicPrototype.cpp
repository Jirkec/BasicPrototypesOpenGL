// BasicPrototype.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <GLFW/glfw3.h>
#include <thread>

int openWindow()
{
    if (!glfwInit())
    {
        // Initialization failed
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        // Window or OpenGL context creation failed
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(window);
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Render here
        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

int main()
{
    std::cout << "Hello World!\n";


    //run the window in a separate thread
    std::thread windowThread(openWindow);
    windowThread.join();

    return 0;
}