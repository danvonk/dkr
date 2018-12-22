//
// Created by dan on 31/10/18.
//

#include "window.h"

using namespace dk::gfx;

Window::Window(GLFWwindow* window, int width, int height, std::string const& cfgFilePath)
    : m_window(window)
    , m_width(width)
    , m_height(height)
    , m_device(new Device(width, height))
    , m_camera(m_width, m_height)
    , m_forwardRenderer(Renderer::RendererType::Forward, m_device.get())
    , m_deferredRenderer(Renderer::RendererType::Deferred, m_device.get())
{
}

Window::~Window() {
}

void Window::setTitle(std::string const &title) {
    glfwSetWindowTitle(m_window, title.c_str());
}

void Window::handleKeyboard(GLFWwindow* window, int key, int scanCode, int actions, int mods) {
    if (key == GLFW_KEY_W && actions == GLFW_REPEAT) {
        m_camera.forward();

    } else if (key == GLFW_KEY_S && actions == GLFW_REPEAT) {
        m_camera.backward();

    } else if (key == GLFW_KEY_A && actions == GLFW_REPEAT) {
        m_camera.left();

    } else if (key == GLFW_KEY_D && actions == GLFW_REPEAT) {
        m_camera.right();
    } else if (key == GLFW_KEY_ESCAPE && actions == GLFW_PRESS) {
        exit(0);
    }
}

void Window::handleMouse(GLFWwindow* window, double xpos, double ypos) {
    m_camera.mouse(xpos, ypos);
}

void Window::init() {
    m_ubo = m_device->createUniformBuffer();
    CameraMatrix cameraMatrix;
    cameraMatrix.proj = m_camera.getProj();
    cameraMatrix.view = m_camera.getView();

    auto& ubuf = m_device->accessUniformBuffer(m_ubo);
    ubuf.bind((void*)&cameraMatrix, sizeof(cameraMatrix));
    ubuf.connectToShader(0);
}

void Window::update(float deltaTime) {
    CameraMatrix cameraMatrix;
    cameraMatrix.proj = m_camera.getProj();
    cameraMatrix.view = m_camera.getView();
    m_device->accessUniformBuffer(m_ubo).bind((void*)&cameraMatrix, sizeof(cameraMatrix));

}



