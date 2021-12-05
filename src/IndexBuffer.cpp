#include "IndexBuffer.h"
#include <GL/glew.h>

IndexBuffer::IndexBuffer(const void* data, unsigned int count) : m_Count(count){

    sizeof(unsigned int) == sizeof(GLuint);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer(){
    glDeleteBuffers(1, &IBO);
}

void IndexBuffer::Bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
}

void IndexBuffer::Unbind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}