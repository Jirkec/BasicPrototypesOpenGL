#version 330
in vec3 color;
in vec2 texCoord;
out vec4 fragment;
uniform sampler2D tex;
void main()
{
    //fragment = vec4(color, 1.0);
    fragment = texture(tex, texCoord);
    //fragment = texture(tex, texCoord) * vec4(color, 1.0);
}