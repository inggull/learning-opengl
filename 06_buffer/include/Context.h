#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "Shader.h"
#include "Program.h"
#include "VertexArray.h"
#include "Buffer.h"

class Context {
public:
    ~Context();
    static std::unique_ptr<Context> Create();
    void Render() const;

private:
    std::unique_ptr<Program> m_program;
    std::unique_ptr<VertexArray> m_vao;
    std::unique_ptr<Buffer> m_vbo;
    std::unique_ptr<Buffer> m_ebo;
    Context() = default;
    bool Init();
};

#endif // __CONTEXT_H__