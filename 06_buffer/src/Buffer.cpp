#include "Buffer.h"

Buffer::~Buffer() {
    glDeleteBuffers(1, &m_buffer);
    spdlog::info("Destroy buffer({})", m_buffer);
}

std::unique_ptr<Buffer> Buffer::CreateWithData(GLenum type, GLsizeiptr dataSize, const void* data, GLenum usage) {
    auto buffer = std::unique_ptr<Buffer>(new Buffer);
    buffer->Init(type, dataSize, data, usage);
    return buffer;
}

void Buffer::Init(GLenum type, GLsizeiptr dataSize, const void* data, GLenum usage) {
    glGenBuffers(1, &m_buffer);
    spdlog::info("Create buffer({})", m_buffer);
    glBindBuffer(type, m_buffer);
    glBufferData(type, dataSize, data, usage);
}

GLuint Buffer::Get() const {
    return m_buffer;
}

void Buffer::Bind() const {
    glBindBuffer(m_type, m_buffer);
}