#ifndef __VERTEX_ARRAY_H__
#define __VERTEX_ARRAY_H__

#include "common.h"

class VertexArray {
public:
    ~VertexArray();
    static std::unique_ptr<VertexArray> Create();
    GLuint Get() const;
    void Set(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);
    void Bind() const;

private:
    GLuint m_vertexArray;
    VertexArray() = default;
    void Init();
};

#endif // __VERTEX_ARRAY_H__