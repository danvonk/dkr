//
// Created by dan on 26/10/18.
//

#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>

using dk::gfx::Camera;

Camera::Camera() {
    m_position = glm::vec3(-4.0f, 1.2f, 1.2f);
    m_target = glm::vec3(0.0f, 0.0f, 0.0f);
    m_up = glm::vec3(0.0f, 0.0f, 1.0f);

    m_pitch = 0.0;
    m_yaw = 0.0;
    m_roll = 0.0;

    m_windowHeight = 720;
    m_windowWidth = 1280;

    m_fov = 45.0f;

    m_nearClip = 1.0f;
    m_farClip = 1000.0f;

    m_aspect = m_windowWidth / m_windowHeight;

    m_proj = glm::perspective(glm::radians(m_fov), m_aspect, m_nearClip, m_farClip);
    m_view = glm::lookAt(m_position, m_target, m_up);

    //update();
}

void Camera::update() {
    glm::quat qPitch = glm::angleAxis(glm::radians(m_pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::quat qYaw = glm::angleAxis(glm::radians(m_yaw), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::quat orientation = qPitch * qYaw;
    orientation = glm::normalize(orientation);
    glm::mat4 rotate = glm::mat4_cast(orientation);

    glm::mat4 translate = glm::mat4(1.0f);
    translate = glm::translate(translate, -m_position);

    m_view = rotate * translate;
}

void Camera::mouse(int x, int y) {
    glm::vec2 mouseDelta = glm::vec2(x,y) - m_mousePosition;

    constexpr auto mouseXsensitivity = 0.1f;
    constexpr auto mouseYsensitivity = 0.1f;

    m_yaw += mouseXsensitivity * mouseDelta.x;
    m_pitch += mouseYsensitivity * mouseDelta.y;

    m_mousePosition = glm::vec2(x,y);
    //update();
}

void Camera::keyDown(const int k) {
    float dx = 0;
    float dz = 0;
//
//    switch (k) {
//        case SDLK_w:
//            dz = 2;
//            break;
//        case SDLK_s:
//            dz = -2;
//            break;
//        case SDLK_a:
//            dx = -2;
//            break;
//        case SDLK_d:
//            dx = 2;
//            break;
//        default:
//            break;
//    }

    glm::mat4& mat = m_view;
    glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
    glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

    constexpr auto speed = 0.12f;
    m_position += (-dz * forward + dx * strafe) * speed;
    //update();
}

void Camera::setPosition(const glm::vec3& pos) {
    m_position = pos;
}