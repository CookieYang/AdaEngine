#version 330 core
out vec4 fragColor;
in vec2 pTexCoord;
uniform sampler2D baseColor;

void main() {
    fragColor = texture(baseColor, pTexCoord);
	//fragColor = vec4(pTexCoord, 0.0, 1.0);
}
