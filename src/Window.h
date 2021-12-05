#pragma once

#include <GLFW/glfw3.h>
#include <string>

class Window {
private:
    GLFWwindow *mainWindow;

public:
    //Initialise GLFW
    Window(int width, int height, const char* title, int majorVersion, int minorVersion);
    //set a context for glew to use
    void setContext();
    bool shouldClose();
    void swapBuffer();
    void pollEvents();
    //Get buffer size information
    void getFrameBuffureSize(int *bufferWidth, int *bufferHeight);
    ~Window();
};