//
// Created by dan on 31/10/18.
//

#ifndef DANKERER_WINDOW_H
#define DANKERER_WINDOW_H

#include "common.h"
#include "renderer.h"
#include "commandBuffer.h"
#include "staticMesh.h"
#include "camera.h"

#include <GLFW/glfw3.h>

namespace dk {
    namespace gfx {
        class ShaderProgram;
        class Texture;
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

            std::unique_ptr<Device> m_renderer;
            std::unique_ptr<Camera> m_camera;
            std::unique_ptr<StaticMesh> m_mesh;
            std::unique_ptr<CommandBuffer> m_cmdBuf;

            GLuint m_vao; //temp

            UniformBufferHandle m_ubo;
        };
    }
}


#endif //DANKERER_WINDOW_H
