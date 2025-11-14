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