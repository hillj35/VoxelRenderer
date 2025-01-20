#version 330 core

in vec2 texcoords;

uniform sampler2D screenColor;

void main() {
    gl_FragColor = texture(screenColor, texcoords);
}