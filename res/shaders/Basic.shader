#shader vertex
#version 330 core

layout (location = 0) in vec4 pos;
layout (location =1) in vec2 tex;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

out vec2 TexCoord;
out vec4 vColor;

mat4 buildTranslate(float x, float y, float z);

void main(){
    float i = gl_InstanceID;
    float x = sin(35.0f*i)*8.0f;
    float y = cos(52.0f*i)*8.0f;
    float z = sin(70.0f*i)*8.0f;
    mat4 trans = model * buildTranslate(x, y, z);
    gl_Position = proj * view * trans * pos;
    vColor = clamp(pos, 0.0f, 1.0f);
    TexCoord = tex;
}

mat4 buildTranslate(float x, float y, float z){
    mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
                      0.0, 1.0, 0.0, 0.0,
                      0.0, 0.0, 1.0, 0.0,
                      x  , y  , z  , 1.0);
    return trans;
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
