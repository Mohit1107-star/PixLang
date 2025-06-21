#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D image;

void main() {
    vec3 color = texture(image, TexCoord).rgb;
    float gray = (color.r + color.g + color.b) / 3.0;
    color = vec3(gray);
    // blur 5 (TODO: add blur kernel)
    // sharpen 2 (not implemented in GLSL yet)
    FragColor = vec4(color, 1.0);
}
