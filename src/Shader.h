#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"

using namespace std;

struct ShaderProgramSource{
    std::string VertexSource;
    std::string fragmentSource;
};

class Shader{
private:
    uint m_RenderID;
    string m_FilePath;
    unordered_map<std::string, int> m_UniformLocationCache;

public:
    Shader(const string& filepath);
    ~Shader();
    void Bind() const;
    void UnBind() const;
    void SetUniform4f(const string& name, float v0, float v1, float v2, float v3);
    void SetUniform1i(const std::string& name, int value);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
    int GetUniformLocation(const string& name);
    uint CreateShader(const string& vertexShader, const std::string& fragmentShader);
    uint CompileShader(uint type, const string& source);
    ShaderProgramSource ParseShader(const string& filePath);
};