//
// Created by dan on 25/10/18.
//

#ifndef DANKERER_RENDERER_H
#define DANKERER_RENDERER_H

#include "common.h"
#include "camera.h"

namespace dk {
    namespace gfx {
        class Renderer {
        public:
            Renderer();
            ~Renderer();

            void setWindowWidth(int w);
            int getWindowWidth();

            void setWindowHeight(int h);
            int getWindowHeight();

            void update();
            void clear();
        private:
            std::string m_deviceVendor;
            std::string m_deviceRenderer;
            std::string m_deviceVersion;

            int m_windowWidth;
            int m_windowHeight;
            GLbitfield m_mask;

            std::unique_ptr<Camera> m_camera;
            GLuint m_vao;
        };
    }
}


#endif //DANKERER_RENDERER_H
