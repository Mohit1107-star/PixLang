cmake_minimum_required(VERSION 3.14)
project(PixelPilot)

set(CMAKE_CXX_STANDARD 17)

add_executable(PixelPilot
    src/main.cpp
    src/glad.c
)

# Include stb_image and glad
target_include_directories(PixelPilot PRIVATE include)

# Add GLFW include path (from Homebrew)
target_include_directories(PixelPilot PRIVATE /opt/homebrew/include)

# Add GLFW lib path (from Homebrew)
target_link_directories(PixelPilot PRIVATE /opt/homebrew/lib)

# Link OpenGL and GLFW
target_link_libraries(PixelPilot
    "-framework OpenGL"
    glfw
)
