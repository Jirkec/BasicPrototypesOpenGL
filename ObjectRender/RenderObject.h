
#include "linmath.h"
#include <filesystem>
#include <glad/gl.h>

typedef struct Vertex
{
    vec3 pos;
    vec3 col;
    vec2 tex; // texture
} Vertex;

class RenderObject
{
public:
    RenderObject();
    ~RenderObject();

    // compiles shaders
    bool Render();

    // updates the object parameters like positon, rotation
    bool Update();

    void SetTexturePath(const std::filesystem::path& path);
    void SetVertexes(const Vertex* vertexes, size_t count);

    void SetPosition(const vec3& position);
    const vec3& GetPosition();

    void SetRotation(float angleDegrees);
    float GetRotation() const;

private:
    GLuint LoadTexture();
    bool LoadShaderCode();

private:
    std::vector<Vertex> vertexes;

    std::filesystem::path texturePath;

    std::filesystem::path fragmentShaderPath;
    char* m_fragmentShaderCode;

    std::filesystem::path vertexShaderPath;
    char* m_vertexShaderCode;

    vec3 m_position;
    float m_angleRotation;
};