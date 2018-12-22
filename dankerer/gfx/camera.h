//
// Created by dan on 26/10/18.
//

#ifndef DANKERER_CAMERA_H
#define DANKERER_CAMERA_H

#include "common.h"

namespace dk {
    namespace gfx {
        struct CameraMatrix {
            glm::mat4 view;
            glm::mat4 proj;

        };
        class Camera {
        public:
            Camera(int width, int height);
            ~Camera() = default;

            void mouse(double x, double y);

            void forward();
            void backward();
            void left();
            void right();

            glm::mat4 getProj();
            glm::mat4 getView();

        private:
            glm::vec3 m_position;
            glm::vec3 m_target;
            glm::vec3 m_up;
            glm::vec3 m_front;

            glm::vec3 m_cameraDirection;
            glm::vec3 m_cameraRight;
            glm::vec3 m_cameraUp;

            glm::vec2 m_lastMouse;
            float m_yaw;
            float m_pitch;

            int m_windowWidth;
            int m_windowHeight;
        };
    }
}


#endif //DANKERER_CAMERA_H
