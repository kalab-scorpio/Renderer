#pragma once

#include <GL/glew.h>
#include<GLFW/glfw3.h>

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

class Camera{
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float moveSpeed;
    float turnSpeed;

    void update();

public:
    Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed);
    ~Camera();
    void keyControl(bool* keys, float deltaTime);
    void mouseControl(float xChange, float yChange);
    glm::mat4 calculateViewMatrix();
};