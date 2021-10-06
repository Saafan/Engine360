#pragma once

#include "glm/fwd.hpp"

static int NumberOfDigits(double n);

void PrintMatrix(glm::mat4 matrix);

bool UniformEquals(int v1, int v2);
bool UniformEquals(unsigned int v1, unsigned int v2);
bool UniformEquals(float v1, float v2);
bool UniformEquals(glm::vec2 v1, glm::vec2 v2);
bool UniformEquals(glm::vec3 v1, glm::vec3 v2);
bool UniformEquals(glm::vec4 v1, glm::vec4 v2);
bool UniformEquals(glm::mat3 v1, glm::mat3 v2);
bool UniformEquals(glm::mat4 v1, glm::mat4 v2);
