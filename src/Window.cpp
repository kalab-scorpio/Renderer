#include <GL/glew.h>
#include "Window.h"
#include <iostream>

Window::Window(const char* title){
    this->width = 800;
    this->height = 600;
    this->title = title;
    for(size_t i = 0; i < 1024; i++)
        keys[i]=0;
}

Window::Window(int width, int height, const char* title){
    this->width = width;
    this->height = height;
    this->title = title;
}  

void Window::Initialise(int majorVersion, int minorVersion){
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

    createCallbacks();
    // glfwSetInputMode(mainWindow,GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    //allow moder extension features
    glewExperimental = GL_TRUE;
    this->setContext();
    //initializing glew
    if(glewInit() != GLEW_OK){
        printf("glew initialisation failed!");
        this->~Window();
        glfwTerminate();
        return;
    }
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CW);
    //setup Viewport size
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    glViewport(0, 0, bufferWidth, bufferHeight);
    float ratio = (float)bufferWidth/(float)bufferHeight;
    proj = glm::perspective(45.0f, ratio, 0.1f, 100.0f);
    glfwSetWindowUserPointer(mainWindow, this);
}

void Window::handlekeys(GLFWwindow* window, int key,int code, int action, int mode){
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetInputMode(window,GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    if(key > 0 && key < 1024){
        if(action == GLFW_PRESS)
            theWindow->keys[key] = true;
        else if(action == GLFW_RELEASE)
            theWindow->keys[key] = false;
    }
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos){
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if(GLFW_CURSOR_DISABLED == glfwGetInputMode(window, GLFW_CURSOR)){
        if(theWindow->firstMoved){
            theWindow->lastx = xPos;
            theWindow->lasty = yPos;
            theWindow->firstMoved = false;
        }
        theWindow->xChange = xPos - theWindow->lastx;
        theWindow->yChange = yPos - theWindow->lasty;

        theWindow->lastx = xPos;
        theWindow->lasty = yPos;
    }
}

void Window::handleMouseButton(GLFWwindow* window, int button, int action, int mode){
     if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        glfwSetInputMode(window,GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::handleResize(GLFWwindow* window, int width, int height){
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    // glfwGetFramebufferSize(window, &theWindow->bufferWidth, &theWindow->bufferHeight);
    glViewport(0, 0, width, height);
    float ratio = (float)width/(float)height;
    theWindow->proj = glm::perspective(45.0f, ratio, 0.1f, 100.0f);
}

MouseChange Window::getMouseChange(){
    MouseChange change = {this->xChange, this->yChange};
    this->xChange=0;
    this->yChange=0;
    return change;
}

void Window::createCallbacks(){
    glfwSetKeyCallback(mainWindow, handlekeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
    glfwSetMouseButtonCallback(mainWindow, handleMouseButton);
    glfwSetWindowSizeCallback(mainWindow, handleResize);
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