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
            Renderer(int width, int height);
            ~Renderer();

            void setWindowWidth(int w);
            int getWindowWidth();

            void setWindowHeight(int h);
            int getWindowHeight();

            Camera* getCamera();
            
            void update();
            void clear();
        private:
            std::string m_deviceVendor;
            std::string m_deviceRenderer;
            std::string m_deviceVersion;

            int m_windowWidth = 640;
            int m_windowHeight = 480;
            GLbitfield m_mask;

            std::unique_ptr<Camera> m_camera;
            GLuint m_vao;
        };
    }
}


#endif //DANKERER_RENDERER_H
