#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D image;

void main()
{
    vec3 color = texture(image, TexCoord).rgb;
    FragColor = vec4(color, 1.0);
}
