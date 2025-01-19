#version 330 core

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
};

in vec3 vertexColor;
in vec3 vertexNormal;

uniform DirectionalLight light;

void main() {
    vec3 lightDir = normalize(-light.direction);
    vec3 normal = normalize(vertexNormal);
    
    float ambientStrength = .5;
    vec3 ambient = ambientStrength * light.ambient;

    float diffuseStrength = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * light.diffuse;

    vec3 color = clamp(diffuse + ambient, vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0)) * vertexColor;

    gl_FragColor = vec4(color, 1.0);
}