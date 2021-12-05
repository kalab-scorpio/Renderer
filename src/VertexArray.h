#pragma once

#include <GL/glew.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

//create vertex array
class VertexArray{
private:
    unsigned int VAO;

public:
    VertexArray();
    ~VertexArray();    

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void Bind() const;
    void Unbind() const;
};