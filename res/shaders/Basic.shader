#shader vertex
#version 330 core

layout (location = 0) in vec4 pos;
uniform mat4 model;
uniform mat4 proj;
out vec4 vColor;

void main(){
    gl_Position = proj * model * pos;
    vColor = clamp(pos, 0.0f, 1.0f);
}

#shader fragment
#version 330 core

out vec4 color;
in vec4 vColor;

void main(){
    color = vec4(0.0f, 0.0f, 1.0f, 1.0f);
    color = vColor;
}
