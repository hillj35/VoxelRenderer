#pragma once
#include <glm/vec3.hpp>

struct DirectionalLight
{
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
};
