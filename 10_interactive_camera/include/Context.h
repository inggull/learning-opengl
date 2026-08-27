#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "Shader.h"
#include "Program.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Image.h"
#include "Texture.h"

class Context {
public:
    ~Context();
    static std::unique_ptr<Context> Create();
    void ProcessInput(GLFWwindow* window);
    void Reshape(int width, int height);
    void MouseMove(double x, double y);
    void MouseButton(int button, int action, int mods, double x, double y);
    void Render();

private:
    std::unique_ptr<Program> m_program;
    std::unique_ptr<VertexArray> m_vao;
    std::unique_ptr<Buffer> m_vbo;
    std::unique_ptr<Buffer> m_ebo;
    std::unique_ptr<Texture> m_tbo1;
    std::unique_ptr<Texture> m_tbo2;
    // camera parameter
    float m_cameraControl { false };
    float m_cameraPitch { 0.0f };
    float m_cameraYaw { 0.0f };
    glm::vec3 m_cameraPos { glm::vec3(0.0f, 0.0f, 0.0f) };
    glm::vec3 m_cameraForward { glm::vec3(0.0f, 0.0f, -1.0f) };
    glm::vec3 m_cameraUp { glm::vec3(0.0f, 1.0f, 0.0f) };
    int m_width { WINDOW_WIDTH };
    int m_height { WINDOW_HEIGHT };
    glm::vec2 m_prevMousePos;
    Context() = default;
    bool Init();
};

#endif // __CONTEXT_H__