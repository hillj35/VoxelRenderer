#version 330 core

int RobertsCrossX[4] = int[](1, 0, 0, -1);
int RobertsCrossY[4] = int[](0, 1, -1, 0);

float CalculateEdge(vec2 uv, vec2 offset, sampler2D color) {
    vec3 samples[4];

    samples[0] = texture(color, uv - offset).rgb;
    samples[1] = texture(color, uv + vec2(offset.x, -offset.y)).rgb;
    samples[2] = texture(color, uv + vec2(-offset.x, offset.y)).rgb;
    samples[3] = texture(color, uv + offset).rgb;

    vec3 horizontal = samples[0] * RobertsCrossX[0] + samples[3] * RobertsCrossX[3];
    vec3 vertical = samples[2] * RobertsCrossY[2] + samples[1] * RobertsCrossY[1];

    return sqrt(dot(horizontal, horizontal) + dot(vertical, vertical));        
}

in vec2 texcoords;

uniform sampler2D screenColor;

void main() {
    vec2 offset = vec2(1.0 / 1920, 1.0 / 1080);
    float edge = CalculateEdge(texcoords, offset, screenColor);
    gl_FragColor = edge > 0 ? vec4(0.0, 0.0, 0.0, 1.0) : texture(screenColor, texcoords);
}