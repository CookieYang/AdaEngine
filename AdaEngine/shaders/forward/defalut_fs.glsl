#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTexCoord;
layout (location = 2) in vec3 vNormal;
layout (location = 3) in vec3 vTangent;
layout (location = 4) in vec3 vBiTangent;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec2 pTexCoord;

void main() {
    pTexCoord = vTexCoord;
   // gl_Position = projMat * viewMat * modelMat * vec4(vPos, 1.0);
	gl_Position = vec4(vPos, 1.0);
}