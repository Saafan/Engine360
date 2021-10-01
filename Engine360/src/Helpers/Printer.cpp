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

static void PrintMatrix(glm::mat4 matrix) {
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

