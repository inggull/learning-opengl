#include "Context.h"

Context::~Context() {
    glDeleteVertexArrays(1, &m_vao);
    spdlog::info("Destroy vertex array({})", m_vao);
}

std::unique_ptr<Context> Context::Create() {
    auto context = std::unique_ptr<Context>(new Context);
    if (!context->Init()) {
        return nullptr;
    }
    return context;
}

bool Context::Init() {
    std::shared_ptr<Shader> vertShader = Shader::CreateFromFile("shader/simple.vert", GL_VERTEX_SHADER);
    if (!vertShader) {
        return false;
    }
    std::shared_ptr<Shader> fragShader = Shader::CreateFromFile("shader/simple.frag", GL_FRAGMENT_SHADER);
    if (!fragShader) {
        return false;
    }
    spdlog::info("Create vertex shader({})", vertShader->Get());
    spdlog::info("Create fragment shader({})", fragShader->Get());

    m_program = Program::Create({vertShader, fragShader});
    if (!m_program) {
        return false;
    }
    spdlog::info("Create program({})", m_program->Get());

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // State-setting function

    glGenVertexArrays(1, &m_vao); // 새로운 VAO를 생성한다
    spdlog::info("Create vertex array({})", m_vao);
    // 셰이더의 전역 변수에 값을 전달한다
    m_program->Use(); // 사용할 프로그램을 지정한다
    glUniform3f(glGetUniformLocation(m_program->Get(), "globalPos"), 0.0f, 0.0f, 0.0f);
    glUniform4f(glGetUniformLocation(m_program->Get(), "globalColor"), 0.8f, 0.7f, 0.7f, 1.0f);

    return true;
}

void Context::Render() const {
    glClear(GL_COLOR_BUFFER_BIT); // State-using function
    glBindVertexArray(m_vao); // 사용할 VAO를 지정한다
    m_program->Use();
    glDrawArrays(GL_POINTS, 0, 1);
}