#pragma once

#include "glm/fwd.hpp"
#include "gl/glew.h"

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


struct Type
{
	Type(unsigned int type, size_t size) { this->type = type; this->size = size; };
	unsigned int type = 0;
	size_t size = 0;
	size_t elementsCount = 0;
	unsigned int count = 0;
};

const GLenum GL_VEC3 = 0;
const GLenum GL_VEC4 = 1;
const GLenum GL_MAT3 = 2;
const GLenum GL_MAT4 = 3;

template <typename type>
static Type ConvertTypeToGLType()
{
	if (typeid(type) == typeid(float)) return Type(GL_FLOAT, sizeof(type));
	if (typeid(type) == typeid(unsigned int)) return Type(GL_UNSIGNED_INT, sizeof(type));
	if (typeid(type) == typeid(int)) return Type(GL_INT, sizeof(type));
	if (typeid(type) == typeid(double)) return Type(GL_DOUBLE, sizeof(type));
	if (typeid(type) == typeid(short)) return Type(GL_SHORT, sizeof(type));
	if (typeid(type) == typeid(unsigned short)) return Type(GL_UNSIGNED_SHORT, sizeof(type));
	if (typeid(type) == typeid(char)) return Type(GL_BYTE, sizeof(type));
	if (typeid(type) == typeid(unsigned char)) return Type(GL_UNSIGNED_BYTE, sizeof(type));
	if (typeid(type) == typeid(glm::vec3)) return Type(GL_VEC3, sizeof(type));
	if (typeid(type) == typeid(glm::vec4)) return Type(GL_VEC4, sizeof(type));
	if (typeid(type) == typeid(glm::mat3)) return Type(GL_MAT3, sizeof(type));
	if (typeid(type) == typeid(glm::mat4)) return Type(GL_MAT4, sizeof(type));
	return Type(GL_INT, 4);
}
