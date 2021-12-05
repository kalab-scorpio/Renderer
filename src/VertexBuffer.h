#pragma once

//creating array buffer
class VertexBuffer{
    private:
    unsigned int VBO;
public:
    /*!
    * @param[in] data Image data using float array
    */
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};