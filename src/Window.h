#pragma once

#include <GLFW/glfw3.h>
#include <string>

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

struct MouseChange{
    float x;
    float y;
};

class Window {
private:
    GLFWwindow *mainWindow;
    int width, height;
    glm::mat4 proj;
    const char* title;
    bool keys[1024];
    int bufferWidth, bufferHeight;
    float lastx, lasty, xChange, yChange;
    bool firstMoved = true;
    static void handlekeys(GLFWwindow* window, int key,int code, int action, int mode);
    static void handleMouse(GLFWwindow* window, double xPos, double yPos);
    static void handleMouseButton(GLFWwindow* window, int button, int action, int mode);
    static void handleResize(GLFWwindow* window, int width, int height);
    void createCallbacks();

public:
    Window(const char* title);
    Window(int width, int height, const char* title);
    MouseChange getMouseChange();
    bool* getkeys() { return keys;}
    glm::mat4 getProjection() { return proj;}
    //set a context for glew to use
    void setContext();
    bool shouldClose();
    void swapBuffer();
    void pollEvents();
    //Initialise GLFW
    void Initialise(int majorVersion, int minorVersion);
    //Get buffer size information
    void getFrameBuffureSize(int *bufferWidth, int *bufferHeight);
    ~Window();
};