#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <fstream>
#include <string>
#include <sstream>

void generate_shader_from_dsl(const std::string& dslPath, const std::string& fragPath) {
    std::ifstream file(dslPath);
    std::string line;
    std::ostringstream shader;

    shader << "#version 330 core\n"
           << "out vec4 FragColor;\n"
           << "in vec2 TexCoord;\n"
           << "uniform sampler2D image;\n\n"
           << "void main() {\n"
           << "    vec3 color = texture(image, TexCoord).rgb;\n";

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string cmd;
        int value = 0;
        iss >> cmd >> value;

        if (cmd == "grayscale") {
            shader << "    float gray = (color.r + color.g + color.b) / 3.0;\n"
                   << "    color = vec3(gray);\n";
        } else if (cmd == "sharpen") {
            shader << "    // sharpen " << value << " (not implemented in GLSL yet)\n";
        } else if (cmd == "blur") {
            shader << "    // blur " << value << " (TODO: add blur kernel)\n";
        } else {
            shader << "    // Unknown command: " << cmd << "\n";
        }
    }

    shader << "    FragColor = vec4(color, 1.0);\n"
           << "}\n";

    std::ofstream out(fragPath);
    out << shader.str();
    std::cout << "✅ Shader generated at: " << fragPath << "\n";
}


// Utility to compile a shader
GLuint compileShader(const char* path, GLenum type) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string src = buffer.str();
    const char* csrc = src.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &csrc, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << "Shader compile error: " << log << std::endl;
    }
    return shader;
}

GLuint createShaderProgram(const char* vertPath, const char* fragPath) {
    GLuint vertShader = compileShader(vertPath, GL_VERTEX_SHADER);
    GLuint fragShader = compileShader(fragPath, GL_FRAGMENT_SHADER);
    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    return program;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "PixelPilot Shader", nullptr, nullptr);
    if (!window) return -1;
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Quad vertices
    float vertices[] = {
        // positions   // texcoords
        -1.0f, -1.0f,   0.0f, 0.0f,
         1.0f, -1.0f,   1.0f, 0.0f,
         1.0f,  1.0f,   1.0f, 1.0f,
        -1.0f,  1.0f,   0.0f, 1.0f
    };
    unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO); glBindVertexArray(VAO);
    glGenBuffers(1, &VBO); glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glGenBuffers(1, &EBO); glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load texture using stb_image
    int w, h, ch;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* img = stbi_load("../assets/sample.jpg", &w, &h, &ch, 3);
    if (!img) {
        std::cerr << "Failed to load image\n";
        return -1;
    }

    GLuint tex;
    glGenTextures(1, &tex); glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(img);

    generate_shader_from_dsl("../filters.dsl", "../shaders/generated.frag");

    // Shader setup
    GLuint shader = createShaderProgram("../shaders/basic.vert", "../shaders/generated.frag");
    glUseProgram(shader);
    glUniform1i(glGetUniformLocation(shader, "image"), 0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader);
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, tex);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
