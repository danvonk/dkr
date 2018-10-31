//
// Created by dan on 31/10/18.
//

#ifndef DANKERER_WINDOW_H
#define DANKERER_WINDOW_H

#include "common.h"
#include "renderer.h"
#include "camera.h"


namespace dk {
    namespace gfx {
        class ShaderProgram;
        class Shader;
        class VertexBuffer;
        class UniformBuffer;

        class Window {
        public:
            Window(GLFWwindow* window, int width, int height);
            ~Window();

            void setTitle(std::string const& title);

            void init();
            void update(float deltaTime);

            //only used for GLFW
            void handleKeyboard(GLFWwindow* window, int key, int scanCode, int actions, int mods);
            //only used for GLFW
            void handleMouse(GLFWwindow* window, double xpos, double ypos);

        private:
            GLFWwindow* m_window;

            int m_width;
            int m_height;
            bool m_vsync;

            std::unique_ptr<dk::gfx::Renderer> m_renderer;
            std::unique_ptr<dk::gfx::Camera> m_camera;

            GLuint m_vao; //temp
            ShaderProgram* m_shp;
            Shader* m_vert;
            Shader* m_frag;
            VertexBuffer* m_vbo;
            UniformBuffer* m_ubo;
        };
    }
}


#endif //DANKERER_WINDOW_H
