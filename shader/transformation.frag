#version 330 core

uniform sampler2D texture0;
uniform sampler2D texture1;

in vec4 vertColor; // vertex shader로부터 입력된 변수로, 같은 변수명에 같은 타입을 사용해야 한다
in vec2 vertTexCoord; // vertex shader로부터 입력된 변수로, 같은 변수명에 같은 타입을 사용해야 한다

out vec4 fragColor; // 최종 출력 색상

void main() {
    vec4 color0 = texture(texture0, vertTexCoord);
    vec4 color1 = texture(texture1, vertTexCoord);
    fragColor = mix(mix(color0, color1, 0.3), vertColor, 0.3);
}