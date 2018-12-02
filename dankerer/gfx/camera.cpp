//
// Created by dan on 26/10/18.
//

#include "camera.h"
#include "gfx/camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>

using dk::gfx::Camera;

Camera::Camera()
    : m_position(glm::vec3(0.0f, 0.0f, 3.0f))
    , m_target(glm::vec3(0.0f, 0.0f, 0.0f))
    , m_up(glm::vec3(0.0f, 1.0f, 0.0f))
    , m_front(glm::vec3(0.0f, 0.0f, -1.0f))

    , m_cameraDirection(glm::normalize(m_position - m_target))
    , m_cameraRight(glm::normalize(glm::cross(m_up, m_cameraDirection)))
    , m_cameraUp(glm::cross(m_cameraDirection, m_cameraRight))

    , m_pitch(0.0f)
    , m_yaw(0.0f)
{
    m_lastMouse = glm::vec2(m_windowWidth / 2, m_windowHeight / 2);
}

Camera::Camera(int width, int height)
: Camera()
{
    m_windowHeight = height;
    m_windowWidth = width;
}

void Camera::mouse(double x, double y) {
    static bool firstMouse = true;
    if (firstMouse) {
        m_lastMouse.x = x;
        m_lastMouse.y = y;
        firstMouse = false;
    }

    float xOffset = x - m_lastMouse.x;
    float yOffset = y - m_lastMouse.y;
    m_lastMouse = glm::vec2(x,y);

    float sensitivity = 0.1f;

    xOffset *= sensitivity;
    yOffset *= sensitivity;

    m_yaw += xOffset;
    m_pitch += yOffset;

    glm::vec3 front;
    front.x = glm::cos(glm::radians(m_yaw) * cos(glm::radians(m_pitch)));
    front.y = glm::sin(glm::radians(m_pitch));
    front.z = glm::sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front = glm::normalize(front);
}


glm::mat4 Camera::getProj() {
    return glm::perspective(glm::radians(45.0f), (float)m_windowWidth / (float) m_windowHeight, 0.1f, 100.0f);
}

glm::mat4 Camera::getView() {
    return glm::lookAt(m_position, m_position + m_front, m_up);;
}

void Camera::forward() {
    m_position += 0.05f * m_front;
}

void Camera::backward(){
    m_position -= 0.05f * m_front;
}

void Camera::left() {
    m_position -= glm::normalize(glm::cross(m_front, m_up)) * 0.05f;
}

void Camera::right() {
    m_position += glm::normalize(glm::cross(m_front, m_up)) * 0.05f;
}