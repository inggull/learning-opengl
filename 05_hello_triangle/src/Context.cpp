#include "Context.h"

Context::~Context() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    spdlog::info("Destroy vertex array({})", m_vao);
    spdlog::info("Destroy vertex buffer({})", m_vbo);
    spdlog::info("Destroy element buffer({})", m_ebo);
}

std::unique_ptr<Context> Context::Create() {
    auto context = std::unique_ptr<Context>(new Context);
    if (!context->Init()) {
        return nullptr;
    }
    return context;
}

bool Context::Init() {
    std::shared_ptr<Shader> vertShader = Shader::CreateFromFile("shader/triangle.vert", GL_VERTEX_SHADER);
    if (!vertShader) {
        return false;
    }
    std::shared_ptr<Shader> fragShader = Shader::CreateFromFile("shader/triangle.frag", GL_FRAGMENT_SHADER);
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

    float vertices[18] = {
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    };
    GLuint indices[3] = {
        0, 1, 2,
    };

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // State-setting function

    // 사용할 VAO가 먼저 바인딩 해줘야 나머지 오르젝트들이 VAO에 저장된다
    glGenVertexArrays(1, &m_vao); // 새로운 VAO를 생성한다
    spdlog::info("Create vertex array({})", m_vao);
    glBindVertexArray(m_vao); // 사용할 VAO를 지정한다

    glGenBuffers(1, &m_vbo); // 새로운 VBO를 생성한다
    spdlog::info("Create vertex buffer({})", m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo); // 사용할 VBO를 지정한다
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // VBO에 데이터를 전달한다

    // 초기에 `VertexAttribPointer`의 포인터는 각 버택스 버퍼에 바인딩된 배열의 시작 주소를 가리켰지만, VAO가 등장하면서 VAO가 가리키는 배열의 오프셋을 의미하게 되었다
    // 속성 0번: position
    glEnableVertexAttribArray(0); // VAO의 0번 속성을 활성화한다
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, reinterpret_cast<const void*>(sizeof(float) * 0)); // VAO의 속성 0번에 해당하는 VBO 데이터를 전달한다
    // 속성 1번: color
    glEnableVertexAttribArray(1); // VAO의 1번 속성을 활성화한다
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, reinterpret_cast<const void*>(sizeof(float) * 3)); // VAO의 속성 1번에 해당하는 VBO 데이터를 전달한다

    glGenBuffers(1, &m_ebo); // 새로운 EBO를 생성한다
    spdlog::info("Create element buffer({})", m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo); // 사용할 EBO를 지정한다
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // EBO에 데이터를 전달한다

    return true;
}

void Context::Render() const {
    glClear(GL_COLOR_BUFFER_BIT); // State-using function
    m_program->Use(); // 사용할 프로그램을 지정한다
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}