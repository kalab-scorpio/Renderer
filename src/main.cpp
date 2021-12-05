#include <iostream>

#include "Renderer.h"
#include "Camera.h"
#include "Window.h"
#include "Texture.h"

#define srcPath "res/shaders/Basic.shader"

// window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14159265f/180.0f;
float deltaTime = 0.0f;
float lastTime = 0.0f;

int bufferWidth, bufferHeight;

int main(){
    Window window("test");
    window.Initialise(3, 3);
    window.setContext();
    window.getFrameBuffureSize(&bufferWidth, &bufferHeight);
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.1f);
    Texture wood("res/Textures/IMG_20211205_191816.jpg");
    Texture road("res/Textures/IMG_20211205_191419.jpg"); 

    float vertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f,  0.5f, 0.0f,
        1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,   0.5f, 1.0f 
    };
    float rawVertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        0.0f, -1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f
    };

    unsigned int indices[]={
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };
        
    VertexArray va;
    IndexBuffer ib(indices, 12);
    VertexBuffer vb(vertices, sizeof(rawVertices));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    
    Shader shader(srcPath);
    
    shader.UnBind();
    ib.Unbind();
    va.Unbind();

    Renderer render;
    
    //Loop until window closed
    while (!window.shouldClose()){
        float now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        window.pollEvents();
        
        camera.keyControl(window.getkeys(), window.getMouseScroll(), deltaTime);
        MouseChange change = window.getMouseChange();
        
        camera.mouseControl(change.x, change.y);
        
        render.Clear();

        shader.Bind();
        shader.SetUniformMat4f("proj", window.getProjection()); 

        glm::mat4 model;
        //model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        // model = glm::rotate(model, x * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        // model = glm::rotate(model, y * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

        shader.SetUniformMat4f("model", model);
        shader.SetUniformMat4f("view", camera.calculateViewMatrix());
        
        va.Bind();
        ib.Bind();
        
        wood.Bind();
        render.Draw(va, ib, shader, 1000000);
        wood.UnBind();
        ib.Unbind();
        va.Unbind();

        shader.UnBind();

        window.swapBuffer();
    }
        
    return 0;
}