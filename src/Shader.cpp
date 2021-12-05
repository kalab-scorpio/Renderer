#include "Shader.h"

Shader::Shader(const string& filePath){
    ShaderProgramSource source = ParseShader(filePath);
    m_RenderID = CreateShader(source.VertexSource, source.fragmentSource);
}

Shader::~Shader(){
    glDeleteProgram(m_RenderID);
}

void Shader::Bind() const{
    glUseProgram(m_RenderID);
}

void Shader::UnBind() const{
    glUseProgram(0);
}

void Shader::SetUniform4f(const string& name, float v0, float v1, float v2, float v3){
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform1i(const std::string& name, int value){
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix){
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const string& name){
    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    int location = glGetUniformLocation(m_RenderID, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform " << name << " doesn\'t exist!" << std::endl;
    
    m_UniformLocationCache[name] = location;
    return location;
}

uint Shader::CreateShader(const string& vertexShader, const std::string& fragmentShader){
    uint program = glCreateProgram();
    uint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    uint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

uint Shader::CompileShader(uint type, const string& source){
    uint id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length* sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        cout<<"Failed to compile "<<(type==GL_VERTEX_SHADER?"vertex":"fragment")<<" shader!"<<endl;
        cout << message << endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

ShaderProgramSource Shader::ParseShader(const string& filepath){
    ifstream stream(filepath);

    enum class ShaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    string line;
    stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line)){
        if(line.find("#shader") != string::npos){
            if(line.find("vertex") != string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != string::npos)
                type = ShaderType::FRAGMENT;
        }

        else{
            ss[(int)type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}
