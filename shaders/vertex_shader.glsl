#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 clr;

out vec3 vColor;

//uniform mat4 mvp;

void main() {
    //gl_Position = mvp * vec4(pos, 1.0);
    gl_Position = vec4(pos, 1.0);
    vColor = clr;
}