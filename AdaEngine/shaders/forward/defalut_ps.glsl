#version 330 core
out vec4 fragColor;
in vec2 pTexCoord;
uniform sampler2D texture0;

void main() {
    fragColor = texture2D(texture0, pTexCoord);
}
