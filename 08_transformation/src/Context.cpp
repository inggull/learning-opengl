#include "Context.h"

Context::~Context() {
    spdlog::info("Destroy context");
}

std::unique_ptr<Context> Context::Create() {
    auto context = std::unique_ptr<Context>(new Context);
    if (!context->Init()) {
        return nullptr;
    }
    return context;
}

bool Context::Init() {
    std::shared_ptr<Shader> vertShader = Shader::CreateFromFile("shader/transformation.vert", GL_VERTEX_SHADER);
    if (!vertShader) {
        return false;
    }
    std::shared_ptr<Shader> fragShader = Shader::CreateFromFile("shader/transformation.frag", GL_FRAGMENT_SHADER);
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

    float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
    0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

    0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
    0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
    0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
    0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
};

uint32_t indices[] = {
    0,  2,  1,  2,  0,  3,
    4,  5,  6,  6,  7,  4,
    8,  9, 10, 10, 11,  8,
    12, 14, 13, 14, 12, 15,
    16, 17, 18, 18, 19, 16,
    20, 22, 21, 22, 20, 23,
};

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // State-setting function

    // 사용할 VAO가 먼저 바인딩 해줘야 나머지 오르젝트들이 VAO에 저장된다
    m_vao = VertexArray::Create(); // 새로운 VAO를 생성한다
    m_vao->Bind(); // 사용할 VAO를 지정한다
    m_vbo = Buffer::CreateWithData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 새로운 VBO를 생성한다
    m_ebo = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // 새로운 EBO를 생성한다

    // 초기에 `VertexAttribPointer`의 포인터는 각 버택스 버퍼에 바인딩된 배열의 시작 주소를 가리켰지만, VAO가 등장하면서 VAO가 가리키는 배열의 오프셋을 의미하게 되었다
    // 속성 0번: position
    m_vao->Set(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<const void*>(sizeof(float) * 0)); // VAO의 0번 속성을 활성화하고, 해당하는 VBO 데이터를 전달한다
    // 속성 2번: texture coordinate
    m_vao->Set(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<const void*>(sizeof(float) * 3)); // VAO의 2번 속성을 활성화하고, 해당하는 VBO 데이터를 전달한다

    std::shared_ptr<Image> container = Image::LoadFromFile("resources/images/container.jpg");
    if (!container) {
        return false;
    }
    spdlog::info("Loaded image file \"resources/images/container.jpg\" ({} x {}, {} channels)", container->GetWidth(), container->GetHeight(), container->GetChannelCount());
    std::shared_ptr<Image> awesomeface = Image::LoadFromFile("resources/images/awesomeface.png");
    if (!awesomeface) {
        return false;
    }
    spdlog::info("Loaded image file \"resources/images/awesomeface.png\" ({} x {}, {} channels)", awesomeface->GetWidth(), awesomeface->GetHeight(), awesomeface->GetChannelCount());

    m_tbo1 = Texture::Create(container);
    m_tbo2 = Texture::Create(awesomeface);

    glActiveTexture(GL_TEXTURE0); // 0번 텍스쳐를 활성화한다
    m_tbo1->Bind(); // 사용할 TBO를 지정한다
    glActiveTexture(GL_TEXTURE1); // 1번 텍스쳐를 활성화한다
    m_tbo2->Bind(); // 사용할 TBO를 지정한다

    m_program->Use(); // 사용할 프로그램을 지정한다
    m_program->SetUniform("texture0", 0); // 프로그램의 전역 변수 `texture0`에 0을 할당한다
    m_program->SetUniform("texture1", 1); // 프로그램의 전역 변수 `texture1`에 1을 할당한다

    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_BLEND);

    return true;
}

void Context::Render() const {
    std::vector<glm::vec3> cubePositions = {
        glm::vec3( -3.0f, 0.0f, -3.0f),
        glm::vec3( 0.0f, 0.0f, -3.0f),
        glm::vec3( 3.0f, 0.0f, -3.0f),
        glm::vec3( -3.0f, 0.0f, 0.0f),
        glm::vec3( 0.0f, 0.0f, 0.0f),
        glm::vec3( 3.0f, 0.0f, 0.0f),
        glm::vec3( -3.0f, 0.0f, 3.0f),
        glm::vec3( 0.0f, 0.0f, 3.0f),
        glm::vec3( 3.0f, 0.0f, 3.0f),
    };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // State-using function
    glEnable(GL_DEPTH_TEST);

    // 종횡비 4:3, 세로 화각 45도로 원근 투영한다 (이 과정에서 오른손 좌표계를 왼손 좌표계로 변환한다)
    auto projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.01f, 20.0f);
    // 카메라를 z축으로 -10만큼 이동시킨다
    auto view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));

    m_program->Use(); // 사용할 프로그램을 지정한다

    for (size_t i = 0; i < cubePositions.size(); ++i) {
        auto& pos = cubePositions[i];
        auto model = glm::translate(glm::mat4(1.0f), pos);
        model = glm::rotate(model, glm::radians((float)glfwGetTime() * 120.0f + 20.0f * (float)i), glm::vec3(1.0f, 0.5f, 0.0f));
        // model -> view -> projection 순으로 선형 변환을 적용한다
        auto transform = projection * view * model;
        // 선형 변환 행렬 값을 쉐이더 파일의 글로벌 변수에 전달한다
        m_program->SetUniform("transform", transform);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    }
}