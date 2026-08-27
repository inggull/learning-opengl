#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "common.h"

class Buffer {
public:
    ~Buffer();
    static std::unique_ptr<Buffer> CreateWithData(GLenum type, GLsizeiptr dataSize, const void* data, GLenum usage);
    GLuint Get() const;
    void Bind() const;

private:
    GLuint m_buffer;
    GLenum m_type;
    GLenum m_usage;
    Buffer() = default;
    void Init(GLenum type, GLsizeiptr dataSize, const void* data, GLenum usage);
};

#endif // __BUFFER_H__