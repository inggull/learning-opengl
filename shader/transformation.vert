#version 330 core

layout (location = 0) in vec3 aPos; // VAO의 0번 속성으로 자동 할당한다
layout (location = 1) in vec3 aColor; // VAO의 1번 속성으로 자동 할당한다
layout (location = 2) in vec2 aTexCoord; // VAO의 2번 속성으로 자동 할당한다

uniform mat4 transform;

out vec4 vertColor; // fragment shader로 넘어갈 색상 값
out vec2 vertTexCoord; // fragment shader로 넘어갈 텍스쳐 좌표 값

void main() {
    gl_Position = transform * vec4(aPos, 1.0); // 반드시 정점의 출력 위치 값을 계산해야 한다
    vertColor = vec4(aColor, 1.0);
    vertTexCoord = aTexCoord;
}