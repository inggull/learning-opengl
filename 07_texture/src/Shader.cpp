#include "Shader.h"

Shader::~Shader() {
    glDeleteShader(m_shader);
    spdlog::info("Destroy shader({})", m_shader);
}

std::unique_ptr<Shader> Shader::CreateFromFile(const std::string& filePath, GLenum type) {
    auto shader = std::unique_ptr<Shader>(new Shader);
    if (!shader->Init(filePath, type)) {
        return nullptr;
    }
    return shader;
}

bool Shader::Init(const std::string& filePath, GLenum type) {
    // Load shader file
    auto text = LoadFile(filePath);
    if (!text) {
        return false;
    }

    int textLength = static_cast<int>(text.value().length());
    const char* chr = text.value().c_str();

    // Create and compile shader
    m_shader = glCreateShader(type); // 쉐이더 핸들을 정수 형태로 반환한다
    glShaderSource(m_shader, 1, &chr, &textLength); // 하나의 쉐이더에 여러 개의 소스 코드를 전달할 수 있다
    glCompileShader(m_shader);

    // Check compile error
    GLint success{};
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
    if (success == 0) {
        char infoLog[1024];
        GLint logLength{};
        glGetShaderInfoLog(m_shader, 1024, &logLength, infoLog);
        infoLog[logLength] = '\0';
        spdlog::error("Failed to compile shader file \"{}\"\n{}", filePath, infoLog);
        return false;
    }

    return true;
}

GLuint Shader::Get() const {
    return m_shader;
}