#pragma once

//creating Element array buffer
class IndexBuffer{
private:
    unsigned int IBO;
    unsigned int m_Count;
public:
    IndexBuffer(const void* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;
    inline unsigned int GetCount() const {return m_Count;}
};