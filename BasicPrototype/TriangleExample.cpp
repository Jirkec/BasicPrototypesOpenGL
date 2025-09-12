#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "linmath.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint LoadTexture(const char* filename)
{
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
    if (!data) {
        fprintf(stderr, "Failed to load texture: %s\n", filename);
        return 0;
    }
    if (width <= 0 || height <= 0) {
        fprintf(stderr, "Invalid image dimensions for %s: %d x %d\n", filename, width, height);
        stbi_image_free(data);
        return 0;
    }
    if (channels != 3 && channels != 4) {
        fprintf(stderr, "Unsupported channel count (%d) in %s\n", channels, filename);
        stbi_image_free(data);
        return 0;
    }

    // Query the maximum supported texture size (do this once, cache if needed)
    GLint maxTexSize = 0;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);

    if (width > maxTexSize || height > maxTexSize) {
        fprintf(stderr, "Texture %s is too large: %dx%d (max supported: %dx%d)\n", filename, width, height, maxTexSize, maxTexSize);
        stbi_image_free(data);
        return 0;
    }

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Set texture parameters (optional, but recommended)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return tex;
}

typedef struct Vertex
{
    vec3 pos;
    vec3 col;
    vec2 tex; // texture
} Vertex;

static const Vertex tetrahedron[] = {
    // Face 1 (Red)
    { { -0.6f, -0.4f, 0.f }, { 1.f, 0.f, 0.f }, { 0.0f, 0.0f } },
    { {  0.6f, -0.4f, 0.f }, { 1.f, 0.f, 0.f }, { 1.0f, 0.0f } },
    { {   0.f,  0.6f,  0.f }, { 1.f, 0.f, 0.f }, { 0.5f, 1.0f } },

    // Face 2 (Green)
    { { -0.6f, -0.4f, 0.f }, { 0.f, 1.f, 0.f }, { 0.0f, 0.0f } },
    { {  0.6f, -0.4f, 0.f }, { 0.f, 1.f, 0.f }, { 1.0f, 0.0f } },
    { {   0.f,  0.f,  0.6f }, { 0.f, 1.f, 0.f }, { 0.5f, 1.0f } },

    // Face 3 (Blue)
    { {  0.6f, -0.4f, 0.f }, { 0.f, 0.f, 1.f }, { 1.0f, 0.0f } },
    { {   0.f,  0.6f,  0.f }, { 0.f, 0.f, 1.f }, { 0.5f, 1.0f } },
    { {   0.f,  0.f,  0.6f }, { 0.f, 0.f, 1.f }, { 0.0f, 0.0f } },

    // Face 4 (Yellow)
    { {   0.f,  0.6f,  0.f }, { 1.f, 1.f, 0.f }, { 0.5f, 1.0f } },
    { { -0.6f, -0.4f, 0.f }, { 1.f, 1.f, 0.f }, { 0.0f, 0.0f } },
    { {   0.f,  0.f,  0.6f }, { 1.f, 1.f, 0.f }, { 1.0f, 0.0f } },
};

static const Vertex cube[] = {
    // Front face (red)
    //triangle 1
    { { -0.5f, -0.5f,  0.5f }, { 1.f, 0.f, 0.f }, { 0.0f, 0.0f } }, // bottom-left
    { {  0.5f, -0.5f,  0.5f }, { 1.f, 0.f, 0.f }, { 1.0f, 0.0f } }, // bottom-right
    { {  0.5f,  0.5f,  0.5f }, { 1.f, 0.f, 0.f }, { 1.0f, 1.0f } }, // top-right
    //triangle 2
    { { -0.5f, -0.5f,  0.5f }, { 1.f, 0.f, 0.f }, { 0.0f, 0.0f } }, // bottom-left
    { {  0.5f,  0.5f,  0.5f }, { 1.f, 0.f, 0.f }, { 1.0f, 1.0f } }, // top-right
    { { -0.5f,  0.5f,  0.5f }, { 1.f, 0.f, 0.f }, { 0.0f, 1.0f } }, // top-left

    // Back face (green)
    { {  0.5f, -0.5f, -0.5f }, { 0.f, 1.f, 0.f }, { 1.0f, 0.0f } }, // bottom-right
    { { -0.5f, -0.5f, -0.5f }, { 0.f, 1.f, 0.f }, { 0.0f, 0.0f } }, // bottom-left
    { { -0.5f,  0.5f, -0.5f }, { 0.f, 1.f, 0.f }, { 0.0f, 1.0f } }, // top-left
    { {  0.5f, -0.5f, -0.5f }, { 0.f, 1.f, 0.f }, { 1.0f, 0.0f } }, // bottom-right
    { { -0.5f,  0.5f, -0.5f }, { 0.f, 1.f, 0.f }, { 0.0f, 1.0f } }, // top-left
    { {  0.5f,  0.5f, -0.5f }, { 0.f, 1.f, 0.f }, { 1.0f, 1.0f } }, // top-right

    // Left face (blue)
    { { -0.5f, -0.5f, -0.5f }, { 0.f, 0.f, 1.f }, { 0.0f, 0.0f } }, // bottom-back
    { { -0.5f, -0.5f,  0.5f }, { 0.f, 0.f, 1.f }, { 1.0f, 0.0f } }, // bottom-front
    { { -0.5f,  0.5f,  0.5f }, { 0.f, 0.f, 1.f }, { 1.0f, 1.0f } }, // top-front
    { { -0.5f, -0.5f, -0.5f }, { 0.f, 0.f, 1.f }, { 0.0f, 0.0f } }, // bottom-back
    { { -0.5f,  0.5f,  0.5f }, { 0.f, 0.f, 1.f }, { 1.0f, 1.0f } }, // top-front
    { { -0.5f,  0.5f, -0.5f }, { 0.f, 0.f, 1.f }, { 0.0f, 1.0f } }, // top-back

    // Right face (yellow)
    { { 0.5f, -0.5f,  0.5f }, { 1.f, 1.f, 0.f }, { 0.0f, 0.0f } }, // bottom-front
    { { 0.5f, -0.5f, -0.5f }, { 1.f, 1.f, 0.f }, { 1.0f, 0.0f } }, // bottom-back
    { { 0.5f,  0.5f, -0.5f }, { 1.f, 1.f, 0.f }, { 1.0f, 1.0f } }, // top-back
    { { 0.5f, -0.5f,  0.5f }, { 1.f, 1.f, 0.f }, { 0.0f, 0.0f } }, // bottom-front
    { { 0.5f,  0.5f, -0.5f }, { 1.f, 1.f, 0.f }, { 1.0f, 1.0f } }, // top-back
    { { 0.5f,  0.5f,  0.5f }, { 1.f, 1.f, 0.f }, { 0.0f, 1.0f } }, // top-front

    // Top face (magenta)
    { { -0.5f,  0.5f,  0.5f }, { 1.f, 0.f, 1.f }, { 0.0f, 0.0f } }, // front-left
    { {  0.5f,  0.5f,  0.5f }, { 1.f, 0.f, 1.f }, { 1.0f, 0.0f } }, // front-right
    { {  0.5f,  0.5f, -0.5f }, { 1.f, 0.f, 1.f }, { 1.0f, 1.0f } }, // back-right
    { { -0.5f,  0.5f,  0.5f }, { 1.f, 0.f, 1.f }, { 0.0f, 0.0f } }, // front-left
    { {  0.5f,  0.5f, -0.5f }, { 1.f, 0.f, 1.f }, { 1.0f, 1.0f } }, // back-right
    { { -0.5f,  0.5f, -0.5f }, { 1.f, 0.f, 1.f }, { 0.0f, 1.0f } }, // back-left

    // Bottom face (cyan)
    { { -0.5f, -0.5f, -0.5f }, { 0.f, 1.f, 1.f }, { 0.0f, 1.0f } }, // back-left
    { {  0.5f, -0.5f, -0.5f }, { 0.f, 1.f, 1.f }, { 1.0f, 1.0f } }, // back-right
    { {  0.5f, -0.5f,  0.5f }, { 0.f, 1.f, 1.f }, { 1.0f, 0.0f } }, // front-right
    { { -0.5f, -0.5f, -0.5f }, { 0.f, 1.f, 1.f }, { 0.0f, 1.0f } }, // back-left
    { {  0.5f, -0.5f,  0.5f }, { 0.f, 1.f, 1.f }, { 1.0f, 0.0f } }, // front-right
    { { -0.5f, -0.5f,  0.5f }, { 0.f, 1.f, 1.f }, { 0.0f, 0.0f } }, // front-left
};


static const char* vertex_shader_text =
R"(
#version 330
uniform mat4 MVP;
in vec3 vPos;
in vec3 vCol;
in vec2 vTex;
out vec3 color;
out vec2 texCoord;
void main()
{
    gl_Position = MVP * vec4(vPos, 1.0);
    color = vCol;
    texCoord = vTex;
}
)";

static const char* fragment_shader_text =
R"(
#version 330
in vec3 color;
in vec2 texCoord;
out vec4 fragment;
uniform sampler2D tex;
void main()
{
    //fragment = vec4(color, 1.0);
    //fragment = texture(tex, texCoord);
    fragment = texture(tex, texCoord) * vec4(color, 1.0);
})";


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
    GLint status = 0;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, buffer);
        fprintf(stderr, "Vertex shader compile error:\n%s\n", buffer);
    }

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(fragment_shader, 512, NULL, buffer);
        fprintf(stderr, "Fragment shader compile error:\n%s\n", buffer);
    }

    const GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetProgramInfoLog(program, 512, NULL, buffer);
        fprintf(stderr, "Shader program link error:\n%s\n", buffer);
    }

    const GLint mvp_location = glGetUniformLocation(program, "MVP");
    const GLint vpos_location = glGetAttribLocation(program, "vPos");
    const GLint vcol_location = glGetAttribLocation(program, "vCol");
    const GLint vtex_location = glGetAttribLocation(program, "vTex");


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
    glEnableVertexAttribArray(vtex_location);
    glVertexAttribPointer(vtex_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex));
    
    //GLuint tetraTextureID = LoadTexture("../..//Resources/Texture/Stone.jpg");
    GLuint tetraTextureID = LoadTexture("D:/Dokumenty/repos/Graphics/BasicPrototype/Resources/Texture/Wood2.jpg");

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
    glEnableVertexAttribArray(vtex_location);
    glVertexAttribPointer(vtex_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex));

    GLuint cubeTextureID = LoadTexture("D:/Dokumenty/repos/Graphics/BasicPrototype/Resources/Texture/Stone.jpg");


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
        mat4x4_translate(t_tetra, -1.0f, 0.0f, -2.0f); // Move a bit to the left
        mat4x4_identity(r_tetra);
        mat4x4_rotate_Y(r_tetra, r_tetra, (float)glfwGetTime());
        mat4x4_mul(m_tetra, t_tetra, r_tetra);
        mat4x4_mul(mvp_tetra, p, m_tetra);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tetraTextureID); // Use the tetrahedron's texture
        glUniform1i(glGetUniformLocation(program, "tex"), 0);

        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp_tetra);
        glBindVertexArray(Tetra_vertex_array_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 12);


        // --- Draw Cube ---
        mat4x4 t_cube, r_cube, m_cube, mvp_cube;
        mat4x4_identity(t_cube);
        mat4x4_translate(t_cube, 1.2f, 0.0f, -2.0f); // Move cube to the right
        mat4x4_identity(r_cube);
        //mat4x4_rotate_X(r_cube, r_cube, (float)glfwGetTime());
        mat4x4_rotate_Y(r_cube, r_cube, (float)glfwGetTime() * 0.5f);
        mat4x4_mul(m_cube, t_cube, r_cube);
        mat4x4_mul(mvp_cube, p, m_cube);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cubeTextureID); // Use the cube's texture
        glUniform1i(glGetUniformLocation(program, "tex"), 0);

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
