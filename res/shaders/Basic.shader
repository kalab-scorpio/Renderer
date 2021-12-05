#shader vertex
#version 330 core

layout (location = 0) in vec4 pos;
layout (location =1) in vec2 tex;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

out vec2 TexCoord;
out vec4 vColor;

void main(){
    gl_Position = proj * view * model * pos;
    vColor = clamp(pos, 0.0f, 1.0f);
    TexCoord = tex;
}

#shader fragment
#version 330 core

out vec4 color;

in vec2 TexCoord;
in vec4 vColor;

uniform sampler2D theTexture;

void main(){
    color = vec4(0.0f, 0.0f, 1.0f, 1.0f);
    color = texture(theTexture, TexCoord);
}
