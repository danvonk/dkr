//
// Created by dan on 31/10/18.
//

#include "window.h"

#include "vertexBuffer.h"
#include "shader.h"
#include "shaderProgram.h"
#include "uniformBuffer.h"


using dk::gfx::Window;
using dk::gfx::Renderer;
using dk::gfx::Camera;

Window::Window(GLFWwindow *window, int width, int height)
    : m_window(window)
    , m_width(width)
    , m_height(height)
    , m_renderer(new Renderer(m_width, m_height))
    , m_camera(new Camera(m_width, m_height))
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    GLfloat vertices[] = {
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

            0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };
    m_vbo = new VertexBuffer();
    m_vbo->bind(vertices, sizeof(vertices));

    m_ubo = new UniformBuffer();
    CameraMatrix cameraMatrix;
    cameraMatrix.proj = m_camera->getProj();
    cameraMatrix.view = m_camera->getView();

    m_ubo->bind((void*)&cameraMatrix, sizeof(cameraMatrix));
    m_ubo->connectToShader(0);

    m_vert = new Shader(GL_VERTEX_SHADER, "dankerer/resources/sh1.vert");
    if (!m_vert->compile()) {
        std::cerr << "Error while compiling vertex shader.\n";
    }

    m_frag = new Shader(GL_FRAGMENT_SHADER, "dankerer/resources/sh1.frag");
    if (!m_frag->compile()) {
        std::cerr << "Error while compiling frag shader.\n";
    }

    m_shp = new ShaderProgram();
    m_shp->addShader(m_vert);
    m_shp->addShader(m_frag);

    if (!m_shp->link()) {
        std::cerr << "Error while compiling shader program.\n";
    }
}

Window::~Window() {
    delete m_ubo;
    delete m_vbo;
    delete m_vert;
    delete m_frag;
    delete m_shp;
}

void Window::setTitle(std::string const &title) {
    glfwSetWindowTitle(m_window, title.c_str());
}

void Window::handleKeyboard(GLFWwindow *window, int key, int scanCode, int actions, int mods) {

}

void Window::handleMouse(GLFWwindow *window, double xpos, double ypos) {

}

void Window::init() {
    CameraMatrix cameraMatrix;
    cameraMatrix.proj = m_camera->getProj();
    cameraMatrix.view = m_camera->getView();

    m_ubo->bind((void*)&cameraMatrix, sizeof(cameraMatrix));
    m_ubo->connectToShader(0);

}

void Window::update(float deltaTime) {
    m_renderer->clear();
    m_camera->update();

    CameraMatrix cameraMatrix;
    cameraMatrix.proj = m_camera->getProj();
    cameraMatrix.view = m_camera->getView();

    m_ubo->bind((void*)&cameraMatrix, sizeof(cameraMatrix));
}



