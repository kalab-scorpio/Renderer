#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed){
    position = startPosition;
    worldUp = startUp;
    yaw = startYaw;
    pitch = startPitch;

    moveSpeed = startMoveSpeed; 
    turnSpeed = startTurnSpeed;

    update();
}

void Camera::update(){
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::mouseControl(float xChange, float yChange){
    xChange *= turnSpeed;
    yChange *= turnSpeed;

    yaw += xChange;

    pitch += yChange;
    // pitch = (pitch > 89.0f? 89.0f : pitch) || (pitch < -89.0f? 0.0f : pitch);
    if(pitch> 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    update();
}

void Camera::keyControl(bool* keys, float deltaTime){
    float speed = moveSpeed * deltaTime;
    if(keys[GLFW_KEY_W])
        position += front * speed;
    if(keys[GLFW_KEY_S])
        position -= front * speed;
    if(keys[GLFW_KEY_D])
        position += right * speed;
    if(keys[GLFW_KEY_A])
        position -= right * speed;
}

glm::mat4 Camera::calculateViewMatrix(){
    return glm::lookAt(position, position + front, up);
}

Camera::~Camera(){}