#include "Window.h"
#include <iostream>

Window::Window(int width, int height, const char* title, int majorVersion, int minorVersion){
    if(!glfwInit()){
        printf("GLFW initialisation failed!");
        glfwTerminate();
    }
    //setup GLFW window properties 
    //Opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    //core profile = no backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    mainWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if(!mainWindow){
        printf("GLFW window creation failed!");
        glfwTerminate();
    } 
}  

void Window::setContext(){
    glfwMakeContextCurrent(mainWindow);
}

bool Window::shouldClose(){
    return glfwWindowShouldClose(mainWindow);
}

void Window::getFrameBuffureSize(int *bufferWidth, int *bufferHeight){
    glfwGetFramebufferSize(mainWindow, bufferWidth, bufferHeight);
}

void Window::swapBuffer(){
    glfwSwapBuffers(mainWindow);
}

void Window::pollEvents(){
    glfwPollEvents();
}

Window::~Window(){
    glfwDestroyWindow(mainWindow);
}