#include "MyTime.h"

MyTime& MyTime::Get() {
    static MyTime instance;
    return instance;
}

void MyTime::Update() {
    m_time = glfwGetTime();
    m_deltaTime = m_time - m_prevTime;
    m_prevTime =  m_time;
}

float MyTime::GetDeltaTime() {
    return (float)m_deltaTime;
}