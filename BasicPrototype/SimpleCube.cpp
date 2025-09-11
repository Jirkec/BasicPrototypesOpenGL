#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

// Vertex Shader
const char* vertShaderSrc = R"(
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
const char* fragShaderSrc = R"(
#version 330 core
in vec3 ourColor;
out vec4 FragColor;
void main()
{
    FragColor = vec4(ourColor, 1.0);
}
)";

// Cube vertices: position (x,y,z), color (r,g,b)
float cubeVertices[] = {
    // positions          // colors
    -0.5f,-0.5f,-0.5f,    1.f,0.f,0.f,
     0.5f,-0.5f,-0.5f,    0.f,1.f,0.f,
     0.5f, 0.5f,-0.5f,    0.f,0.f,1.f,
    -0.5f, 0.5f,-0.5f,    1.f,1.f,0.f,
    -0.5f,-0.5f, 0.5f,    1.f,0.f,1.f,
     0.5f,-0.5f, 0.5f,    0.f,1.f,1.f,
     0.5f, 0.5f, 0.5f,    1.f,1.f,1.f,
    -0.5f, 0.5f, 0.5f,    0.f,0.f,0.f,
};
// Cube indices for 12 triangles (36 indices)
unsigned int cubeIndices[] = {
    0,1,2, 2,3,0,   // Back face
    4,5,6, 6,7,4,   // Front face
    4,5,1, 1,0,4,   // Bottom face
    6,7,3, 3,2,6,   // Top face
    4,7,3, 3,0,4,   // Left face
    5,6,2, 2,1,5    // Right face
};

// Minimal 4x4 matrix operations for MVP (nicer with GLM, but this works!)
void multiplyMat4(float* res, const float* a, const float* b) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            res[i * 4 + j] = 0.f;
            for (int k = 0; k < 4; ++k)
                res[i * 4 + j] += a[i * 4 + k] * b[k * 4 + j];
        }
}

// Perspective matrix ("camera lens")
void perspective(float* mat, float fovy, float aspect, float znear, float zfar) {
    float tanHalfFovy = tanf(fovy / 2.f);
    for (int i = 0; i < 16; ++i) mat[i] = 0.f;
    mat[0] = 1.f / (aspect * tanHalfFovy);
    mat[5] = 1.f / tanHalfFovy;
    mat[10] = -(zfar + znear) / (zfar - znear);
    mat[11] = -1.f;
    mat[14] = -(2.f * zfar * znear) / (zfar - znear);
}

// Simple translation
void translate(float* mat, float x, float y, float z) {
    for (int i = 0; i < 16; ++i) mat[i] = (i % 5 == 0) ? 1.f : 0.f; // identity
    mat[12] = x; mat[13] = y; mat[14] = z;
}

// Simple rotation about Y axis
void rotateY(float* mat, float angle) {
    for (int i = 0; i < 16; ++i) mat[i] = (i % 5 == 0) ? 1.f : 0.f;
    float c = cosf(angle), s = sinf(angle);
    mat[0] = c;  mat[2] = s;
    mat[8] = -s; mat[10] = c;
}

int main3() {
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Spinning Cube", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "GLAD could not load OpenGL\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST); // Enable depth buffering

    // Vertex Array, Buffers
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    // Attributes: position and color
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Compile & link shaders
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertShader); // no longer needed after linking
    glDeleteShader(fragShader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
        std::cerr << "Vertex Shader compilation failed:\n" << infoLog << std::endl;
    }
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cerr << "Fragment Shader compilation failed:\n" << infoLog << std::endl;
    }
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader Program linking failed:\n" << infoLog << std::endl;
    }

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Build MVP matrix manually
        float proj[16], view[16], model[16], mv[16], mvp[16];

        perspective(proj, 3.14159f / 4.f, 800.f / 600.f, 0.1f, 100.f);
        translate(view, 0.f, 0.f, -3.f);
        rotateY(model, (float)glfwGetTime());
        multiplyMat4(mv, view, model);
        multiplyMat4(mvp, proj, mv);

        // Render cube
        glUseProgram(shaderProgram);
        int mvpLoc = glGetUniformLocation(shaderProgram, "MVP");
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, mvp);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}