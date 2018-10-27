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
            ~Camera();

            void mouse(int x, int y);
            void keyDown(const int k);

            void setPosition(const glm::vec3& pos);

            void update();

            auto getProj() {
                return m_proj;
            }

            auto getView() {
                return m_view;
            }

            auto getWindowHeight() {
                return m_windowHeight;
            }

            auto getWindowWidth() {
                return m_windowWidth;
            }

            auto getPosition() {
                return m_position;
            }

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
