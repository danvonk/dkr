//
// Created by dan on 31/10/18.
//

#ifndef DANKERER_WINDOW_H
#define DANKERER_WINDOW_H

#include "common.h"
#include "renderer.h"
#include "staticMesh.h"
#include "camera.h"
#include "sceneLoader.h"

#include <GLFW/glfw3.h>

namespace dk {
    namespace gfx {
        class Window {
        public:
            Window(GLFWwindow* window, int width, int height, std::string const& cfgFilePath, std::string const& sceneFilePath);
            ~Window();

            void setTitle(std::string const& title);

            void init();
            void update(float deltaTime);

            //only used for GLFW
            void handleKeyboard(GLFWwindow* window, int key, int scanCode, int actions, int mods);
            //only used for GLFW
            void handleMouse(GLFWwindow* window, double xpos, double ypos);

        private:
            struct ConfigFile {
                Renderer::RendererType m_rendType = Renderer::RendererType::Forward;
                u32 m_msaa;

                bool m_tiledLighting = false;
                bool m_hdrBloom = false;
                bool m_showUI = false;
                bool m_ssao = false;
            } m_configFile;

            void readConfigFile(std::string const& path);

            GLFWwindow* m_window;
            //only one opengl context/device should be created per application
            std::unique_ptr<Device> m_device;

            int m_width;
            int m_height;
            bool m_vsync;

            Renderer m_forwardRenderer;
            Renderer m_deferredRenderer;

            Camera m_camera;

            SceneLoader m_sceneLoader;

            GLuint m_vao; //temp

            UniformBufferHandle m_ubo;
        };
    }
}


#endif //DANKERER_WINDOW_H
