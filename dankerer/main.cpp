#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include "glm/glm.hpp"

#include "gfx/renderer.h"
#include "gfx/vertexBuffer.h"
#include "gfx/shader.h"
#include "gfx/shaderProgram.h"

#include <experimental/filesystem>

using namespace dk::gfx;
namespace fs = std::experimental::filesystem;

int main() {
    if (!glfwInit()) {
        std::cerr << "Could not start GLFW\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "DanVonkRenderer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Could not open window\n";
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLfloat vertices[] = {
            0.0f,  0.5f,
            0.5f, -0.5f,
            -0.5f, -0.5f
    };

    VertexBuffer vbo2;
    vbo2.bind(vertices, sizeof(vertices));

    Shader vertex(GL_VERTEX_SHADER, "dankerer/resources/sh1.vert");
    if (!vertex.compile()) {
        std::cerr << "Error while compiling vertex shader.\n";
    }

    Shader fragment(GL_FRAGMENT_SHADER, "dankerer/resources/sh1.frag");
    if (!fragment.compile()) {
        std::cerr << "Error while compiling frag shader.\n";
    }

    ShaderProgram shp;
    shp.addShader(&vertex);
    shp.addShader(&fragment);
    if (!shp.link()) {
        std::cerr << "Error while compiling shader program.\n";
    }

    Renderer renderer;
    renderer.clear();


    while (!glfwWindowShouldClose(window)) {

        renderer.clear();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glfwTerminate();
    return 0;
}
