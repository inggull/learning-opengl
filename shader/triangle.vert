#version 330 core
layout (location = 0) in vec3 aPos; // VAO의 0번 속성으로 자동 할당한다
layout (location = 1) in vec3 aColor; // VAO의 1번 속성으로 자동 할당한다

out vec4 vertColor; // fragment shader로 넘어갈 색상 값

void main() {
    gl_Position = vec4(aPos, 1.0); // 반드시 정점의 출력 위치 값을 계산해야 한다
    vertColor = vec4(aColor, 1.0);
}