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

bool UniformEquals(int v1, int v2)
{
	return v1 == v2;
}

bool UniformEquals(unsigned int v1, unsigned int v2)
{
	return v1 == v2;
}

bool UniformEquals(float v1, float v2)
{
	return v1 == v2;
}

bool UniformEquals(glm::vec2 v1, glm::vec2 v2)
{
	return (v1.x == v2.x && v1.y == v2.y);
}

bool UniformEquals(glm::vec3 v1, glm::vec3 v2)
{
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}

bool UniformEquals(glm::vec4 v1, glm::vec4 v2)
{
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w);
}

bool UniformEquals(glm::mat3 v1, glm::mat3 v2)
{
	for (size_t i = 0; i < 3; i++)
		for (size_t j = 0; j < 3; j++)
			if (v1[i][j] != v2[i][j])
				return false;
	return true;
}

bool UniformEquals(glm::mat4 v1, glm::mat4 v2)
{
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			if (v1[i][j] != v2[i][j])
				return false;
	return true;
}

