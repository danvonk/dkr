//
// Created by dan on 25/10/18.
//

#ifndef DANKERER_RENDERER_H
#define DANKERER_RENDERER_H

#include "common.h"
#include "camera.h"
#include <GLFW/glfw3.h>

namespace dk {
    namespace gfx {
        class Renderer {
        public:
            Renderer(int width, int height);
            ~Renderer();

            void setWindowWidth(int w);
            int getWindowWidth();

            void setWindowHeight(int h);
            int getWindowHeight();

            void executeCommandBuffer();
            void clear();
        private:
            std::string m_deviceVendor;
            std::string m_deviceRenderer;
            std::string m_deviceVersion;

            int m_windowWidth;
            int m_windowHeight;
            GLbitfield m_mask;

        };
    }
}


#endif //DANKERER_RENDERER_H
