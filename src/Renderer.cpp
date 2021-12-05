#include "Renderer.h"

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const{
    shader.Bind();
    va.Bind();
    ib.Bind();
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, int primCount)const{
    shader.Bind();
    va.Bind();
    ib.Bind();
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0,primCount);
}

void Renderer::Clear(float r, float g, float b, float a)const{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Clear() const{
    // glClearColor(0.0f, 0.3f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}