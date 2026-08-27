#include "common.h"
#include "Shader.h"
#include "Program.h"
#include "Context.h"

void OnFramebufferSizeEvent(GLFWwindow* window, int width, int height);
void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
void OnCursorPosEvent(GLFWwindow* window, double x, double y);
void OnMouseButtonEvent(GLFWwindow* window, int button, int action, int mods);

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

    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeEvent);
    glfwSetKeyCallback(window, OnKeyEvent);
    glfwSetCursorPosCallback(window, OnCursorPosEvent);
    glfwSetMouseButtonCallback(window, OnMouseButtonEvent);

    auto context = Context::Create();
    if (!context) {
        return -1;
    }
    glfwSetWindowUserPointer(window, context.get());

    // Strat main loop
    spdlog::info("Start main loop");
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        context->ProcessInput(window);
        context->Render();
        glfwSwapBuffers(window);
        TIME.Update();
    }

    // 소멸자 호출
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void OnFramebufferSizeEvent(GLFWwindow* window, int width, int height) {
    spdlog::info("FramebufferSize changed: {} x {}", width, height);
    reinterpret_cast<Context*>(glfwGetWindowUserPointer(window))->Reshape(width, height);
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

void OnCursorPosEvent(GLFWwindow* window, double x, double y) {
    spdlog::info("CursorPos changed: {} x {}", x, y);
    reinterpret_cast<Context*>(glfwGetWindowUserPointer(window))->MouseMove(x, y);
}

void OnMouseButtonEvent(GLFWwindow* window, int button, int action, int mods) {
    spdlog::info("button: {}, action: {}, mods: {}{}{}",
        button, action,
        ((mods & GLFW_MOD_CONTROL) ? "C" : "-"),
        ((mods & GLFW_MOD_SHIFT) ? "S" : "-"),
        ((mods & GLFW_MOD_ALT) ? "A" : "-")
    );
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    reinterpret_cast<Context*>(glfwGetWindowUserPointer(window))->MouseButton(button, action, mods, x, y);
}