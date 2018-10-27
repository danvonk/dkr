//
// Created by dan on 25/10/18.
//

#include "renderer.h"
#include "dankerer/gfx/renderer.h"


using dk::gfx::Renderer;

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
