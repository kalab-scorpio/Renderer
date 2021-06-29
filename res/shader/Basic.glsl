#shader vertex
#version 330 core

layout (location = 0) in vec3 pos;
uniform mat4 model;
out vec4 vColor;

void main(){
    gl_Position = model * vec4(pos, 1.0f);
    vColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
}

#shader fragment
#version 330 core

out vec4 color;
in vec4 vColor;

void main(){
    color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    color = vColor;
}