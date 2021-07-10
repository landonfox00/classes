/*
 * test.cpp
 *
 * Test driver for Gaussian Dataset code
 *
 * Author: Logan Leavitt
 *
 */
#include <iostream>
#include "dataset.h"

int main() {
	GaussianDataset d1({1, 1}, {1, 1});
	GaussianDataset d2({4, 4}, {1, 1});

	d1.generateSamples(60);
	d2.generateSamples(140);

	std::cout << "Dataset 1:" << std::endl;

	for (auto it = d1.data.begin(); it != d1.data.end(); ++it) {
		std::cout << '\t' << (*it)[0] << ", " << (*it)[1] << std::endl;
	}

	std::cout << "Dataset 2:" << std::endl;

	for (auto it = d2.data.begin(); it != d2.data.end(); ++it) {
		std::cout << '\t' << (*it)[0] << ", " << (*it)[1] << std::endl;
	}

	return 0;
}
