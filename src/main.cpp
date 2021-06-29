#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>

#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"
#include "lib/glm/gtc/type_ptr.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14159265f/180.0f;

GLuint VAO, VBO, shader, uniformModel;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;

struct ShaderProgramSource{
    std::string VertexSource;
    std::string fragmentSource;
};

ShaderProgramSource ParseShader(const std::string& fileapath){
    std::ifstream stream(fileapath);

    enum class ShaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line)){
        if(line.find("#shader") != std::string::npos){
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }

        else{
            ss[(int)type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}


ShaderProgramSource source = ParseShader("res/shader/Basic.glsl");

void CreateTriangle(){
  float vertices[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
  };
  //creating vertex array
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  //creating 
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void AddShader(GLint theProgram,std::string& shaderCode, GLenum shaderType){
  GLuint theShader = glCreateShader(shaderType);
  
  const GLchar* theCode = shaderCode.c_str();

  GLint codeLength[1];
  codeLength[0] = strlen(theCode);

  glShaderSource(theShader, 1, &theCode, codeLength);
  glCompileShader(theShader);

  GLint result = 0;
  GLchar eLog[1024] = { 0 };

  glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
  if(!result){
    glGetProgramInfoLog(theShader, sizeof(eLog), NULL, eLog);
    printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
    return;
  }

  glAttachShader(theProgram, theShader);
}

void CompileShader(){
  shader = glCreateProgram();
  if(!shader){
    printf("Error creating shader program!\n");
    return;
  }

  AddShader(shader, source.VertexSource, GL_VERTEX_SHADER);
  AddShader(shader, source.fragmentSource, GL_FRAGMENT_SHADER);

  GLint result = 0;
  GLchar eLog[1024] = { 0 };
  
  glLinkProgram(shader);
  glGetProgramiv(shader, GL_LINK_STATUS, &result);
  if(!result){
    glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
    printf("Error linking program: '%s'\n", eLog);
    return;
  }

  glValidateProgram(shader);
  glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
  if(!result){
    glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
    printf("Error Validating program: '%s'\n", eLog);
    return;
  }

  uniformModel = glGetUniformLocation(shader, "model");
}


int main(){
  //Initialise GLFW
  if(!glfwInit()){
    printf("GLFW initialisation failed!");
    glfwTerminate();
    return 1;
  }

  //setup GLFW window properties 
  //Opengl version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //core profile = no backwards compatibility
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
  if(!mainWindow){
    printf("GLFW window creation failed!");
    glfwTerminate();
    return 1;
  } 

  //Get buffer size information
  // int bufferWidth, bufferHeight;
  // glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

  //set a context for glew to use
  glfwMakeContextCurrent(mainWindow);

  //allow moder extension features
  glewExperimental = GL_TRUE;

  //initializing glew
  if(glewInit() != GLEW_OK){
    printf("glew initialisation failed!");
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    return 1;
  }

  //setup Viewport size
  // glViewport(0, 0, bufferWidth, bufferHeight);
  CreateTriangle();
  CompileShader();

  //Loop until window closed
  while (!glfwWindowShouldClose(mainWindow)){
    //Get + Handle user input events
    glfwPollEvents();   

    if(direction)
      triOffset += triIncrement;
    else
      triOffset -= triIncrement;
    
    if(abs(triOffset) >= triMaxOffset)
      direction = !direction;

    //clear window
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader);

    glm::mat4 model;
    // model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
    // model = glm::rotate(model, 45 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);

    glUseProgram(0);

    glfwSwapBuffers(mainWindow);
  }
  
  return 0;
}