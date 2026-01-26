#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 iPos;
layout (location = 2) in float iSize;
layout (location = 3) in vec3 iColor;

out vec3 vColor;

void main() {
	vec2 pos = aPos * iSize + iPos;
	gl_Position = vec4(pos, 0.0, 1.0);
	vColor = iColor;
}
