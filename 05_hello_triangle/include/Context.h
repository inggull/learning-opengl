#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "Shader.h"
#include "Program.h"

class Context {
public:
    ~Context();
    static std::unique_ptr<Context> Create();
    void Render() const;

private:
    std::unique_ptr<Program> m_program;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
    Context() = default;
    bool Init();
};

#endif // __CONTEXT_H__