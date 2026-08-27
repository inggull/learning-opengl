#include "Program.h"

Program::~Program() {
    glDeleteProgram(m_program);
    spdlog::info("Destroy program({})", m_program);
}

std::unique_ptr<Program> Program::Create(const std::vector<std::shared_ptr<Shader>>& shaders) {
    auto program = std::unique_ptr<Program>(new Program);
    if (!program->Init(shaders)) {
        return nullptr;
    }
    return program;
}

bool Program::Init(const std::vector<std::shared_ptr<Shader>>& shaders) {
    m_program = glCreateProgram();
    for (auto& shader : shaders) {
        glAttachShader(m_program, shader->Get());
    }
    glLinkProgram(m_program);

    // Check link error
    GLint success{};
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (success == 0) {
        char infoLog[1024];
        GLint logLength{};
        glGetProgramInfoLog(m_program, 1024, &logLength, infoLog);
        infoLog[logLength] = '\0';
        spdlog::error("Failed to link program\n{}", infoLog);
        return false;
    }

    return true;
}

GLuint Program::Get() const {
    return m_program;
}

void Program::Use() const {
    glUseProgram(m_program);
}

void Program::SetUniform(const std::string& name, int value) const {
    auto loc = glGetUniformLocation(m_program, name.c_str());
    glUniform1i(loc, value);
}

void Program::SetUniform(const std::string& name, const glm::mat4& value) const {
    auto loc = glGetUniformLocation(m_program, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}