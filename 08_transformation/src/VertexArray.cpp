#include "VertexArray.h"

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_vertexArray);
    spdlog::info("Destroy vertex array({})", m_vertexArray);
}

std::unique_ptr<VertexArray> VertexArray::Create() {
    auto vertexArray = std::unique_ptr<VertexArray>(new VertexArray);
    vertexArray->Init();
    return vertexArray;
}

void VertexArray::Init() {
    glGenVertexArrays(1, &m_vertexArray);
    spdlog::info("Create vertex array({})", m_vertexArray);
}

GLuint VertexArray::Get() const {
    return m_vertexArray;
}

void VertexArray::Set(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
}

void VertexArray::Bind() const {
    glBindVertexArray(m_vertexArray);
}