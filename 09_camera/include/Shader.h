#ifndef __SHADER_H__
#define __SHADER_H__

#include "common.h"

class Shader {
public:
    ~Shader();
    static std::unique_ptr<Shader> CreateFromFile(const std::string& filePath, GLenum type);
    GLuint Get() const;

private:
    GLuint m_shader;
    Shader() = default;
    bool Init(const std::string& filePath, GLenum type);
};

#endif // __SHADER_H__