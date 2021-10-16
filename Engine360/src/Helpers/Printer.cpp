#include "Printer.h"

#include "glm/glm.hpp"
#include <sstream>
#include <iomanip>
#include <iostream>

static int NumberOfDigits(double n) {
	int m;
	std::ostringstream strs;
	strs << n;
	std::string str = strs.str();
	m = str.size();
	return m;
}

void PrintMatrix(glm::mat4 matrix) {
	const size_t nmax = 100;
	int maxLengthPerColumn[nmax];
	const int m = 4;
	const int n = 4;
	for (int i = 0; i < m; i++) {
		int maxLength = 0;
		for (int j = 0; j < n; j++) {
			int num_length = NumberOfDigits(matrix[i][j]);
			if (num_length > maxLength) {
				maxLength = num_length;
			}
		}
		maxLengthPerColumn[i] = maxLength;
	}

	for (int j = 0; j < n; j++) {
		std::cout << std::endl << std::setw(2) << "|" << std::setw(1);
		for (int i = 0; i < m; i++) {
			const int maxLength = maxLengthPerColumn[j] + 1;
			std::cout << std::setw(maxLength);
			std::cout << matrix[i][j];
			if (i == m - 1) std::cout << std::setw(1) << " |";
		}
	}
}


void PrintValue(GLenum dataType, const void* value)
{
	switch (dataType)
	{
	case GL_FLOAT:
		std::cout << *(float*)(value) << std::endl;
		break;
	case GL_INT:
		std::cout << *(int*)(value) << std::endl;
		break;
	case GL_UNSIGNED_INT:
		std::cout << *(unsigned int*)(value) << std::endl;
		break;
	case GL_DOUBLE:
		std::cout << *(double*)(value) << std::endl;
		break;
	case GL_VEC3:
		const glm::vec3 valueVector3 = *(glm::vec3*)(value);
		std::cout << "(x: " << valueVector3.x << ", y:" << valueVector3.y << ", z:" << valueVector3.z << ")" << std::endl;
		break;
	case GL_VEC4:
		const glm::vec4 valueVector4 = *(glm::vec4*)(value);
		std::cout << "(x: " << valueVector4.x << ", y:" << valueVector4.y << ", z:" << valueVector4.z << ", w: " << valueVector4.w << ")" << std::endl;
		break;
	case GL_MAT4:
		const glm::mat4 valueMatrix = *(glm::mat4*)(value);
		PrintMatrix(valueMatrix);
		break;
	}
}