#include <iostream>

#include "Renderer.h"
#include "Window.h"

#define srcPath "res/shaders/Basic.shader"

// window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14159265f/180.0f;

GLuint uniformModel, uniformProj;
int bufferWidth, bufferHeight;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;

int main(){
    Window window(WIDTH, HEIGHT, "Test", 3, 3);
    window.getFrameBuffureSize(&bufferWidth, &bufferHeight);
    window.setContext();

    //allow moder extension features
    glewExperimental = GL_TRUE;

    //initializing glew
    if(glewInit() != GLEW_OK){
        printf("glew initialisation failed!");
        window.~Window();
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);
    //setup Viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);
    
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    unsigned int indices[]={
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    glm::mat4 proj = glm::perspective(45.0f, (GLfloat)bufferWidth/bufferHeight, 0.1f, 100.0f);
        
    VertexArray va;
    IndexBuffer ib(indices, 12);
    VertexBuffer vb(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    va.AddBuffer(vb, layout);
    
    Shader shader(srcPath);
    shader.Bind();
    shader.SetUniformMat4f("proj", proj);
    
    shader.UnBind();
    ib.Unbind();
    va.Unbind();

    Renderer render;

    //Loop until window closed
    while (!window.shouldClose()){
        //Get + Handle user input events
        window.pollEvents();

        if(direction)
        triOffset += triIncrement;
        else
        triOffset -= triIncrement;
        
        if(abs(triOffset) >= triMaxOffset)
        direction = !direction;

        //clear window
        render.Clear();

        shader.Bind();

        glm::mat4 model;
        model = glm::translate(model, glm::vec3(0.0f, triOffset, -2.5f));
        // model = glm::rotate(model, triOffset * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

        shader.SetUniformMat4f("model", model);
        
        va.Bind();
        ib.Bind();
        render.Draw(va, ib, shader);
        ib.Unbind();
        va.Unbind();

        shader.UnBind();

        window.swapBuffer();
    }
        
    return 0;
}