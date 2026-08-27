#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "common.h"
#include "Shader.h"

class Program {
public:
    ~Program();
    static std::unique_ptr<Program> Create(const std::vector<std::shared_ptr<Shader>>& shaders);
    GLuint Get() const;
    void Use() const;
    void SetUniform(const std::string& name, int value) const;
    void SetUniform(const std::string& name, const glm::mat4& value) const;

private:
    GLuint m_program;
    Program() = default;
    bool Init(const std::vector<std::shared_ptr<Shader>>& shaders);
};

#endif // __PROGRAM_H__