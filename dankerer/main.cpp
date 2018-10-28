#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <experimental/filesystem>
#include <fstream>

#include "glm/glm.hpp"

#include "gfx/renderer.h"
#include "gfx/vertexBuffer.h"
#include "gfx/shader.h"
#include "gfx/shaderProgram.h"
#include "gfx/uniformBuffer.h"
#include "gfx/texture.h"
#include "gfx/mesh.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace dk::gfx;
namespace fs = std::experimental::filesystem;

void errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    std::cout << "OpenGL Error: " << message << '\n';
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Could not start GLFW\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifndef NDEBUG
    std::cout << "Running in debug mode!\n";
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "DanVonkRenderer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Could not open window\n";
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

#ifndef NDEBUG
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(errorCallback, nullptr);
    GLuint unusedIds = 0;
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, GL_TRUE);
#endif

//    Renderer renderer(800, 600);
//    renderer.clear();

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

//    Mesh mesh;
//    mesh.loadOBJ("dankerer/resources/chalet.obj");
    VertexBuffer vbo;
    vbo.bind(nullptr, 0);

    Texture tex;
    tex.loadImage("dankerer/resources/sample.png");

//    UniformBuffer ubo;
    struct CameraMatrix {
        glm::mat4 view;
        glm::mat4 proj;

    } cameraMatrix;

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);
    glm::mat4 view = glm::lookAt(
            glm::vec3(2.5f, 2.5f, 2.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 1.0f)
    );

//    ubo.bind((void*)&cameraMatrix, sizeof(cameraMatrix));
//    ubo.connectToShader(0);


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

    auto uView = glGetUniformLocation(shp.getID(), "view");
    auto uProj = glGetUniformLocation(shp.getID(), "proj");

    glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(uProj, 1, GL_FALSE, glm::value_ptr(proj));

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        GLenum err;
        while ((err = glGetError() != GL_NO_ERROR)) {
            std::cerr << "glGetError() returns: " << err << '\n';
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
