// BasicPrototype.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <thread>

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int openWindow()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        // Initialization failed
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        // Window or OpenGL context creation failed
        glfwTerminate();
        return -1;
    }
    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    float cubeVertices[] = {
        // positions           // colors
        -0.5f,-0.5f,-0.5f,     1.0f,0.0f,0.0f,
         0.5f,-0.5f,-0.5f,     0.0f,1.0f,0.0f,
         0.5f, 0.5f,-0.5f,     0.0f,0.0f,1.0f,
        -0.5f, 0.5f,-0.5f,     1.0f,1.0f,0.0f,
        -0.5f,-0.5f, 0.5f,     1.0f,0.0f,1.0f,
         0.5f,-0.5f, 0.5f,     0.0f,1.0f,1.0f,
         0.5f, 0.5f, 0.5f,     1.0f,1.0f,1.0f,
        -0.5f, 0.5f, 0.5f,     0.0f,0.0f,0.0f,
    };
    unsigned int cubeIndices[] = {
        0,1,2, 2,3,0, // back
        4,5,6, 6,7,4, // front
        4,5,1, 1,0,4, // bottom
        6,7,3, 3,2,6, // top
        4,7,3, 3,0,4, // left
        5,6,2, 2,1,5  // right
    };

    // Positions: x, y, z
    float verticesTriangle[] = {
         0.0f,  0.5f, 0.0f,   // Top
        -0.5f, -0.5f, 0.0f,   // Bottom Left
         0.5f, -0.5f, 0.0f    // Bottom Right
    };

    /*
    VBO = Vertex Buffer Object (stores all your vertex data: positions, colors, etc.)
    EBO = Element Buffer Object (also called Index Buffer; tells OpenGL which vertices form triangles)
    VAO = Vertex Array Object (remembers your buffer settings and layout, for easy re-use)
    */
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    // positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Vertex Shader
    const char* vertShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform mat4 MVP;
out vec3 ourColor;
void main()
{
    gl_Position = MVP * vec4(aPos, 1.0);
    ourColor = aColor;
}
)";
    // Fragment Shader
    const char* fragShaderSource = R"(
#version 330 core
in vec3 ourColor;
out vec4 FragColor;
void main()
{
    FragColor = vec4(ourColor, 1.0);
}
)";

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Render here
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        const float ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);


        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

int main2()
{
    std::cout << "Hello World!\n";


    //run the window in a separate thread
    std::thread windowThread(openWindow);
    windowThread.join();

    return 0;
}