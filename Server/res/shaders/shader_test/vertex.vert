#version 430

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iColour;

out vec3 v2fColour;

void main() {
	v2fColour = iColour;

	gl_Position = vec4(iPosition, 1);
}
