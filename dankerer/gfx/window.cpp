//
// Created by dan on 31/10/18.
//

#include "window.h"

#include "vertexBuffer.h"
#include "shader.h"
#include "shaderProgram.h"
#include "uniformBuffer.h"
#include "texture.h"

using dk::gfx::Window;
using dk::gfx::Renderer;
using dk::gfx::Texture;
using dk::gfx::Camera;
using dk::gfx::StaticMesh;

Window::Window(GLFWwindow* window, int width, int height)
    : m_window(window)
    , m_width(width)
    , m_height(height)
    , m_renderer(new Renderer(m_width, m_height))
    , m_camera(new Camera(m_width, m_height))
    , m_cmdBuf(new CommandBuffer())
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
}

Window::~Window() {
    m_renderer->deleteUniformBuffer(m_ubo);

    glDeleteVertexArrays(1, &m_vao);
}

void Window::setTitle(std::string const &title) {
    glfwSetWindowTitle(m_window, title.c_str());
}

void Window::handleKeyboard(GLFWwindow* window, int key, int scanCode, int actions, int mods) {
    if (key == GLFW_KEY_W && actions == GLFW_REPEAT) {
        m_camera->forward();

    } else if (key == GLFW_KEY_S && actions == GLFW_REPEAT) {
        m_camera->backward();

    } else if (key == GLFW_KEY_A && actions == GLFW_REPEAT) {
        m_camera->left();

    } else if (key == GLFW_KEY_D && actions == GLFW_REPEAT) {
        m_camera->right();
    } else if (key == GLFW_KEY_ESCAPE && actions == GLFW_PRESS) {
        exit(0);
    }
}

void Window::handleMouse(GLFWwindow* window, double xpos, double ypos) {
    m_camera->mouse(xpos, ypos);
}

void Window::init() {
    m_mesh = std::make_unique<StaticMesh>();
    m_mesh->loadFromFile("C:/Users/dan/dev/dkr/dankerer/resources/living_room.obj", *m_renderer);

    m_ubo = m_renderer->createUniformBuffer();
    CameraMatrix cameraMatrix;
    cameraMatrix.proj = m_camera->getProj();
    cameraMatrix.view = m_camera->getView();

    auto& ubuf = m_renderer->accessUniformBuffer(m_ubo);
    ubuf.bind((void*)&cameraMatrix, sizeof(cameraMatrix));
    ubuf.connectToShader(0);
}

void Window::update(float deltaTime) {
    m_renderer->clear();

    CameraMatrix cameraMatrix;
    cameraMatrix.proj = m_camera->getProj();
    cameraMatrix.view = m_camera->getView();
    m_renderer->accessUniformBuffer(m_ubo).bind((void*)&cameraMatrix, sizeof(cameraMatrix));

    //add mesh to the render queue
    m_mesh->render(m_cmdBuf.get());
    m_renderer->submit(m_cmdBuf.get());

//    glDrawElements(GL_TRIANGLES, m_mesh->m_vertCount, GL_UNSIGNED_INT, 0);
//    for (auto i = 0; i < m_mesh->m_subMeshes.size(); i++) {
//        const auto& mc = m_mesh->m_subMeshes[i];
//        glDrawElements(GL_TRIANGLES, mc.m_vertexCount, GL_UNSIGNED_INT, (void*)(mc.m_startElement * 3 * sizeof(u32)));
//    }
}



