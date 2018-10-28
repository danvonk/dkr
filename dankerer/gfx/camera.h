//
// Created by dan on 26/10/18.
//

#ifndef DANKERER_CAMERA_H
#define DANKERER_CAMERA_H

#include "common.h"

namespace dk {
    namespace gfx {
        class Camera {
        public:
            Camera();
            Camera(int width, int height);
            ~Camera() = default;

            void mouse(int x, int y);
            void keyDown(int k);

            void setPosition(const glm::vec3& pos);

            void update();

            glm::mat4 getProj();
            glm::mat4 getView();

            void setWindowHeight(int h);
            int getWindowHeight();
            void setWindowWidth(int w);
            int getWindowWidth();

        private:
            int m_windowHeight;
            int m_windowWidth;

            float m_aspect;
            float m_fov;
            float m_nearClip;
            float m_farClip;

            glm::vec3 m_position;
            glm::vec3 m_up;
            glm::vec3 m_target;

            glm::mat4 m_proj;
            glm::mat4 m_view;

            glm::vec2 m_mousePosition;

            float m_pitch;
            float m_roll;
            float m_yaw;
        };
    }
}


#endif //DANKERER_CAMERA_H
