#include <imgui.h>

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

    glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a); // State-setting function

    // 사용할 VAO가 먼저 바인딩 해줘야 나머지 오르젝트들이 VAO에 저장된다
    m_vao = VertexArray::Create(); // 새로운 VAO를 생성한다
    m_vao->Bind(); // 사용할 VAO가 지정
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

void Context::ProcessInput(GLFWwindow* window) {
    if (!m_cameraControl) {
        return;
    }

    float cameraSpeed = 10.0f;
    auto cameraRight = glm::normalize(glm::cross(m_cameraUp, -m_cameraForward));
    auto cameraUp = glm::cross(-m_cameraForward, cameraRight);
    glm::vec3 move = glm::vec3(0.0f, 0.0f, 0.0f);

    switch (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
        case GLFW_PRESS:
            cameraSpeed = 20.0f;
            break;
        case GLFW_RELEASE:
            cameraSpeed = 10.0f;
            break;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        move += m_cameraForward;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        move -= m_cameraForward;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        move -= cameraRight;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        move += cameraRight;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        move += cameraUp;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        move -= cameraUp;
    }
    if (move.x || move.y || move.z) {
        m_cameraPos += glm::normalize(move) * cameraSpeed * TIME.GetDeltaTime();
        // spdlog::info("camera pos: [{}, {}, {}]", m_cameraPos.x, m_cameraPos.y, m_cameraPos.z);
    }
}

void Context::Reshape(int width, int height) {
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void Context::MouseMove(double x, double y) {
    if (m_cameraControl) {
        auto pos = glm::vec2((float)x, (float)y);
        auto deltaPos = pos - m_prevMousePos;
        m_prevMousePos = pos;
        const float cameraRotationSpeed = 30.0f;
        if (m_cameraControl) {
            m_cameraPitch -= deltaPos.y * cameraRotationSpeed * TIME.GetDeltaTime();
            m_cameraYaw -= deltaPos.x * cameraRotationSpeed * TIME.GetDeltaTime();
            if (89.0f < m_cameraPitch) {
                m_cameraPitch = 89.0f;
            }
            if (m_cameraPitch < -89.0f) {
                m_cameraPitch = -89.0f;
            }
            if (m_cameraYaw < 0.0f) {
                m_cameraYaw += 360.0f;
            }
            if (360.0f < m_cameraYaw) {
                m_cameraYaw -= 360.0f;
            }
        }
    }
}

void Context::MouseButton(int button, int action, int mods, double x, double y) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            m_prevMousePos = glm::vec2((float)x, (float)y);
            m_cameraControl = true;
        }
    }
    if (m_cameraControl && button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        m_cameraControl = false;
    }
}

void Context::Render() {
    if (ImGui::Begin("UI Window")) {
        ImGui::ColorEdit4("clear color", glm::value_ptr(m_clearColor));
        glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
        ImGui::Separator();
        ImGui::DragFloat3("camera pos", glm::value_ptr(m_cameraPos), 0.01f);
        ImGui::DragFloat("camera pitch", &m_cameraPitch, 0.5f, -89.0f, 89.0f);
        ImGui::DragFloat("camera yaw", &m_cameraYaw, 0.5f, -360.0f, 360.0f);
        if (ImGui::Button("reset camera")) {
            m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
            m_cameraPitch = 0.0f;
            m_cameraYaw = 0.0f;
        }
    }
    ImGui::End();

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

    // 동차 좌표계의 마지막 자리에 1.0f 대신에 0.0f이 들어감으로써 위치 벡터가 아닌 방향 벡터 연산이 가능하다
    m_cameraForward = glm::rotate(glm::mat4(1.0f), glm::radians(m_cameraYaw), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_cameraPitch), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);

    // 종횡비 4:3, 세로 화각 45도로 원근 투영한다 (이 과정에서 오른손 좌표계를 왼손 좌표계로 변환한다)
    auto projection = glm::perspective(glm::radians(45.0f), (float)m_width / (float)m_height, 0.01f, 20.0f);
    auto view = glm::lookAt(m_cameraPos , m_cameraPos + m_cameraForward, m_cameraUp);

    m_program->Use(); // 사용할 프로그램을 지정한다

    for (size_t i = 0; i < cubePositions.size(); ++i) {
        auto& pos = cubePositions[i];
        auto model = glm::translate(glm::mat4(1.0f), pos);
        // model = glm::rotate(model, glm::radians((float)glfwGetTime() * 120.0f + 20.0f * (float)i), glm::vec3(1.0f, 0.5f, 0.0f));
        // model -> view -> projection 순으로 선형 변환을 적용한다
        auto transform = projection * view * model;
        // 선형 변환 행렬 값을 쉐이더 파일의 글로벌 변수에 전달한다
        m_program->SetUniform("transform", transform);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    }
}