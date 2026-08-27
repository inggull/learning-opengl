#include "common.h"
#include "Shader.h"
#include "Program.h"

#define WINDOW_NAME "Program"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

void OnFramebufferSizeEvent(GLFWwindow* window, int width, int height);
void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
    // Initialize glfw
    spdlog::info("Initialize glfw");
    if (glfwInit() == GLFW_FALSE) {
        spdlog::error("Failed to initialize glfw");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create glfw window
    spdlog::info("Create glfw window");
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    if (!window) {
        spdlog::error("Failed to create glfw window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize glad
    spdlog::info("Initialize glad");
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        spdlog::error("Failed to initialize glad");
        glfwTerminate();
        return -1;
    }
    auto glVersion = glGetString(GL_VERSION);
    spdlog::info("Loaded OpenGL {}", reinterpret_cast<const char*>(glVersion));
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); // State-setting function
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // State-setting function

    std::shared_ptr<Shader> vertShader = Shader::CreateFromFile("shader/simple.vert", GL_VERTEX_SHADER);
    if (!vertShader) {
        return -1;
    }
    std::shared_ptr<Shader> fragShader = Shader::CreateFromFile("shader/simple.frag", GL_FRAGMENT_SHADER);
    if (!fragShader) {
        return -1;
    }
    spdlog::info("Create vertex shader({})", vertShader->Get());
    spdlog::info("Create fragment shader({})", fragShader->Get());

    auto program = Program::Create({vertShader, fragShader});
    if (!program) {
        return -1;
    }
    spdlog::info("Create program({})", program->Get());

    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeEvent);
    glfwSetKeyCallback(window, OnKeyEvent);

    // Strat main loop
    spdlog::info("Start main loop");
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT); // State-using function
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void OnFramebufferSizeEvent(GLFWwindow* window, int width, int height) {
    spdlog::info("FramebufferSize changed: {} x {}", width, height);
    glViewport(0, 0, width, height);
}

void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
    spdlog::info("key: {}, scancode: {}, action: {}, mods: {}{}{}",
        key, scancode,
        action == GLFW_PRESS ? "Press" :
        action == GLFW_RELEASE ? "Release" :
        action == GLFW_REPEAT ? "Repeat" : "Unknown",
        ((mods & GLFW_MOD_CONTROL) ? "C" : "-"),
        ((mods & GLFW_MOD_SHIFT) ? "S" : "-"),
        ((mods & GLFW_MOD_ALT) ? "A" : "-")
    );

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}