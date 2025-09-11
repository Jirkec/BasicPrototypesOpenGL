#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "linmath.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

typedef struct Vertex
{
    vec3 pos;
    vec3 col;
} Vertex;

static const Vertex vertices[4] =
{
    { { -0.6f, -0.4f, 0.f }, { 1.f, 0.f, 0.f } },
    { {  0.6f, -0.4f, 0.f }, { 0.f, 1.f, 0.f } },
    { {   0.f,  0.6f,  0.f }, { 0.f, 0.f, 1.f } },
    { {   0.f,  0.f,  0.6f }, { 0.f, 0.f, 1.f } },
};

static const Vertex tetrahedron[] = {
    // Face 1 (Red)
    { { -0.6f, -0.4f, 0.f }, { 1.f, 0.f, 0.f } },
    { {  0.6f, -0.4f, 0.f }, { 1.f, 0.f, 0.f } },
    { {   0.f,  0.6f,  0.f }, { 1.f, 0.f, 0.f } },

    // Face 2 (Green)
    { { -0.6f, -0.4f, 0.f }, { 0.f, 1.f, 0.f } },
    { {  0.6f, -0.4f, 0.f }, { 0.f, 1.f, 0.f } },
    { {   0.f,  0.f,  0.6f }, { 0.f, 1.f, 0.f } },

    // Face 3 (Blue)
    { {  0.6f, -0.4f, 0.f }, { 0.f, 0.f, 1.f } },
    { {   0.f,  0.6f,  0.f }, { 0.f, 0.f, 1.f } },
    { {   0.f,  0.f,  0.6f }, { 0.f, 0.f, 1.f } },

    // Face 4 (Yellow)
    { {   0.f,  0.6f,  0.f }, { 1.f, 1.f, 0.f } },
    { { -0.6f, -0.4f, 0.f }, { 1.f, 1.f, 0.f } },
    { {   0.f,  0.f,  0.6f }, { 1.f, 1.f, 0.f } },
};

static const Vertex cube[] = {
    // Front face (red)
    { { -0.5f, -0.5f,  0.5f }, { 1.f, 0.f, 0.f } },
    { {  0.5f, -0.5f,  0.5f }, { 1.f, 0.f, 0.f } },
    { {  0.5f,  0.5f,  0.5f }, { 1.f, 0.f, 0.f } },
    { { -0.5f, -0.5f,  0.5f }, { 1.f, 0.f, 0.f } },
    { {  0.5f,  0.5f,  0.5f }, { 1.f, 0.f, 0.f } },
    { { -0.5f,  0.5f,  0.5f }, { 1.f, 0.f, 0.f } },

    // Back face (green)
    { {  0.5f, -0.5f, -0.5f }, { 0.f, 1.f, 0.f } },
    { { -0.5f, -0.5f, -0.5f }, { 0.f, 1.f, 0.f } },
    { { -0.5f,  0.5f, -0.5f }, { 0.f, 1.f, 0.f } },
    { {  0.5f, -0.5f, -0.5f }, { 0.f, 1.f, 0.f } },
    { { -0.5f,  0.5f, -0.5f }, { 0.f, 1.f, 0.f } },
    { {  0.5f,  0.5f, -0.5f }, { 0.f, 1.f, 0.f } },

    // Left face (blue)
    { { -0.5f, -0.5f, -0.5f }, { 0.f, 0.f, 1.f } },
    { { -0.5f, -0.5f,  0.5f }, { 0.f, 0.f, 1.f } },
    { { -0.5f,  0.5f,  0.5f }, { 0.f, 0.f, 1.f } },
    { { -0.5f, -0.5f, -0.5f }, { 0.f, 0.f, 1.f } },
    { { -0.5f,  0.5f,  0.5f }, { 0.f, 0.f, 1.f } },
    { { -0.5f,  0.5f, -0.5f }, { 0.f, 0.f, 1.f } },

    // Right face (yellow)
    { { 0.5f, -0.5f,  0.5f }, { 1.f, 1.f, 0.f } },
    { { 0.5f, -0.5f, -0.5f }, { 1.f, 1.f, 0.f } },
    { { 0.5f,  0.5f, -0.5f }, { 1.f, 1.f, 0.f } },
    { { 0.5f, -0.5f,  0.5f }, { 1.f, 1.f, 0.f } },
    { { 0.5f,  0.5f, -0.5f }, { 1.f, 1.f, 0.f } },
    { { 0.5f,  0.5f,  0.5f }, { 1.f, 1.f, 0.f } },

    // Top face (magenta)
    { { -0.5f,  0.5f,  0.5f }, { 1.f, 0.f, 1.f } },
    { {  0.5f,  0.5f,  0.5f }, { 1.f, 0.f, 1.f } },
    { {  0.5f,  0.5f, -0.5f }, { 1.f, 0.f, 1.f } },
    { { -0.5f,  0.5f,  0.5f }, { 1.f, 0.f, 1.f } },
    { {  0.5f,  0.5f, -0.5f }, { 1.f, 0.f, 1.f } },
    { { -0.5f,  0.5f, -0.5f }, { 1.f, 0.f, 1.f } },

    // Bottom face (cyan)
    { { -0.5f, -0.5f, -0.5f }, { 0.f, 1.f, 1.f } },
    { {  0.5f, -0.5f, -0.5f }, { 0.f, 1.f, 1.f } },
    { {  0.5f, -0.5f,  0.5f }, { 0.f, 1.f, 1.f } },
    { { -0.5f, -0.5f, -0.5f }, { 0.f, 1.f, 1.f } },
    { {  0.5f, -0.5f,  0.5f }, { 0.f, 1.f, 1.f } },
    { { -0.5f, -0.5f,  0.5f }, { 0.f, 1.f, 1.f } },
};


static const char* vertex_shader_text =
"#version 330\n"
"uniform mat4 MVP;\n"
"in vec3 vCol;\n"
"in vec3 vPos;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 1.0);\n"
"    color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"#version 330\n"
"in vec3 color;\n"
"out vec4 fragment;\n"
"void main()\n"
"{\n"
"    fragment = vec4(color, 1.0);\n"
"}\n";

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST);
    //glDisable(GL_CULL_FACE);

    glfwSwapInterval(1);

    //shaders setup
    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    const GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    const GLint mvp_location = glGetUniformLocation(program, "MVP");
    const GLint vpos_location = glGetAttribLocation(program, "vPos");
    const GLint vcol_location = glGetAttribLocation(program, "vCol");


    //tetragon setup
    GLuint Tetra_vertex_buffer_VBO;
    glGenBuffers(1, &Tetra_vertex_buffer_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, Tetra_vertex_buffer_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tetrahedron), tetrahedron, GL_STATIC_DRAW);

    GLuint Tetra_vertex_array_VAO;
    glGenVertexArrays(1, &Tetra_vertex_array_VAO);
    glBindVertexArray(Tetra_vertex_array_VAO);

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,sizeof(Vertex), (void*)offsetof(Vertex, col));


    //cube setup
    GLuint Cube_vertex_buffer_VBO;
    glGenBuffers(1, &Cube_vertex_buffer_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, Cube_vertex_buffer_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

    GLuint Cube_vertex_array_VAO;
    glGenVertexArrays(1, &Cube_vertex_array_VAO);
    glBindVertexArray(Cube_vertex_array_VAO);

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));


    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        const float ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mat4x4 p;
        mat4x4_perspective(p, 1.0f, ratio, 0.1f, 10.0f);

        glUseProgram(program);

        // --- Draw Tetrahedron ---
        mat4x4 t_tetra, r_tetra, m_tetra, mvp_tetra;
        mat4x4_identity(t_tetra);
        mat4x4_translate(t_tetra, 0.0f, 0.0f, -2.0f); // Center
        mat4x4_identity(r_tetra);
        mat4x4_rotate_Y(r_tetra, r_tetra, (float)glfwGetTime());
        mat4x4_mul(m_tetra, t_tetra, r_tetra);
        mat4x4_mul(mvp_tetra, p, m_tetra);

        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp_tetra);
        glBindVertexArray(Tetra_vertex_array_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 12);

        // --- Draw Cube ---
        mat4x4 t_cube, r_cube, m_cube, mvp_cube;
        mat4x4_identity(t_cube);
        mat4x4_translate(t_cube, 1.2f, 0.0f, -2.0f); // Move cube to the right
        mat4x4_identity(r_cube);
        mat4x4_rotate_X(r_cube, r_cube, (float)glfwGetTime());
        mat4x4_rotate_Y(r_cube, r_cube, (float)glfwGetTime() * 0.5f);
        mat4x4_mul(m_cube, t_cube, r_cube);
        mat4x4_mul(mvp_cube, p, m_cube);

        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp_cube);
        glBindVertexArray(Cube_vertex_array_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
