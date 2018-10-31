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
            Camera();
            Camera(int width, int height);
            ~Camera() = default;

            void mouse(int x, int y);

            void forward();
            void backward();
            void left();
            void right();


            void setPosition(const glm::vec3& pos);

            void update();

            glm::mat4 getProj();
            glm::mat4 getView();

            void setWindowHeight(int h);
            int getWindowHeight();
            void setWindowWidth(int w);
            int getWindowWidth();

        private:
            glm::vec3 m_position;
            glm::vec3 m_front;
            glm::vec3 m_up;
            glm::vec3 m_right;
            glm::vec3 m_worldUp;

            glm::mat4 m_view;
            glm::mat4 m_proj;

            float m_yaw;
            float m_pitch;

            float m_mouseSensitivity;
            float m_movementSpeed;
            float m_zoom;

            int m_windowWidth;
            int m_windowHeight;
        };
    }
}


#endif //DANKERER_CAMERA_H
