//
// Created by dan on 26/10/18.
//

#include "camera.h"
#include "dankerer/gfx/camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>

using dk::gfx::Camera;

Camera::Camera()
    : m_position(glm::vec3(-4.0f, 1.2f, 1.2f))
    , m_front(glm::vec3(0.0f, 0.0f, 0.0f))
    , m_up(glm::vec3(0.0f, 0.0f, 1.0f))
    , m_yaw(-90.0f)
    , m_pitch(0.0f)
    , m_movementSpeed(2.5f)
    , m_mouseSensitivity(0.1f)
    , m_zoom(45.0f)
{
}

Camera::Camera(int width, int height)
: Camera()
{
    m_windowHeight = height;
    m_windowWidth = width;
}

void Camera::mouse(int x, int y) {
//    glm::vec2 mouseDelta = glm::vec2(x, y) - m_mousePosition;
//
//    constexpr auto mouseXsensitivity = 0.01f;
//    constexpr auto mouseYsensitivity = 0.01f;
//
//    m_yaw += mouseXsensitivity * mouseDelta.x;
//    m_pitch += mouseYsensitivity * mouseDelta.y;
//
//    m_mousePosition = glm::vec2(x, y);
//    update();
}


void Camera::setPosition(const glm::vec3 &pos) {
    m_position = pos;
}

glm::mat4 Camera::getProj() {
    return glm::perspective(glm::radians(m_zoom), (float)m_windowWidth / (float) m_windowHeight, 0.1f, 100.0f);
}

glm::mat4 Camera::getView() {
    return glm::lookAt(glm::vec3(-4.0f, 1.2f, 1.2f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Camera::setWindowHeight(int h) {
    m_windowHeight = h;
}

int Camera::getWindowWidth() {
    return m_windowWidth;
}

int Camera::getWindowHeight() {
    return m_windowHeight;
}

void Camera::setWindowWidth(int w) {
    m_windowWidth = w;
}

void Camera::forward() {
    float dx = 0;
    float dz = 2;

    glm::mat4 &mat = m_view;
    glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
    glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

    constexpr auto speed = 0.12f;
    m_position += (-dz * forward + dx * strafe) * speed;
    update();
}

void Camera::backward(){
    float dx = 0;
    float dz = -2;

    glm::mat4 &mat = m_view;
    glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
    glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

    constexpr auto speed = 0.12f;
    m_position += (-dz * forward + dx * strafe) * speed;
    update();
}

void Camera::left() {
    float dx = -2;
    float dz = 0;

    glm::mat4 &mat = m_view;
    glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
    glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

    constexpr auto speed = 0.12f;
    m_position += (-dz * forward + dx * strafe) * speed;
    update();
}

void Camera::right() {
    float dx = 2;
    float dz = 0;

    glm::mat4 &mat = m_view;
    glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
    glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

    constexpr auto speed = 0.12f;
    m_position += (-dz * forward + dx * strafe) * speed;
    update();
}

void Camera::update() {
//    auto roll = glm::mat4(1.0f);
//    auto pitch = glm::mat4(1.0f);
//    auto yaw = glm::mat4(1.0f);
//
//    roll = glm::rotate(roll, m_roll, glm::vec3(0.0f, 0.0f, 1.0f));
//    pitch = glm::rotate(pitch, m_pitch, glm::vec3(1.0f, 0.0f, 0.0f));
//    yaw = glm::rotate(yaw, m_yaw, glm::vec3(0.0f, 1.0f, 0.0f));
//
//    auto rotate = roll * pitch * yaw;
//    glm::mat4 translate = glm::translate(translate, -m_position);
//
//    m_view = rotate * translate;
}
