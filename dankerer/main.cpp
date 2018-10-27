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

    Renderer renderer;
    renderer.setWindowWidth(640);
    renderer.setWindowHeight(480);

    renderer.clear();

    Mesh mesh;
    mesh.loadOBJ("dankerer/resources/teapot.obj");

    Texture tex;
    tex.loadImage("dankerer/resources/chalet.jpg");

    UniformBuffer ubo;
    struct CameraMatrix {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;

    } cameraMatrix;
    cameraMatrix.proj = renderer.getCamera()->getProj();
    cameraMatrix.view = renderer.getCamera()->getView();
    ubo.bind((void*)&cameraMatrix, sizeof(cameraMatrix));
    ubo.connectToShader(0);


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

    while (!glfwWindowShouldClose(window)) {
        renderer.clear();
        glDrawArrays(GL_TRIANGLES, 0, mesh.getVertCount());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}
