#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texPistol;

void main()
{
    FragColor = texture(texPistol, TexCoord);
}
