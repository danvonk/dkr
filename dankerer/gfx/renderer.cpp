//
// Created by dan on 25/10/18.
//

#include "renderer.h"
#include "camera.h"


#include <cstring>

using dk::gfx::Camera;
using dk::gfx::Renderer;

Renderer::Renderer(int width, int height)
{
    m_windowWidth = width;
    m_windowHeight = height;

    const GLubyte *vendorString = glGetString(GL_VENDOR);
    auto deviceRenderer = glGetString(GL_RENDERER);
    auto deviceVersion = glGetString(GL_VERSION);

    m_deviceVendor = std::string((const char *) vendorString,
                                 std::strlen(reinterpret_cast<const char *>(vendorString)));
    m_deviceRenderer = std::string((const char *) deviceRenderer, std::strlen((const char *) deviceRenderer));
    m_deviceVersion = std::string((const char *) deviceVersion, std::strlen((const char *) deviceVersion));

    m_mask = GL_COLOR_BUFFER_BIT;
}

Renderer::~Renderer() {
}

void Renderer::clear() {
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setWindowWidth(int w) {
    m_windowWidth = w;
}

int Renderer::getWindowWidth() {
    return m_windowWidth;
}

void Renderer::setWindowHeight(int h) {
    m_windowHeight = h;
}

int Renderer::getWindowHeight() {
    return m_windowHeight;
}
