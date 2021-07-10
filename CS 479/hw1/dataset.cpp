/*
 * dataset.cpp
 *
 * Implements GaussianDataset class
 *
 * Used to generate random samples from a 2D Gaussian Distribution
 * x and y are assumed to be independent
 *
 * Author: Logan Leavitt
 *
 */

#include <iostream>
#include <vector>
#include <exception>
#include "dataset.h"

double ranf();
double box_muller(double, double);

GaussianDataset::GaussianDataset(
		std::vector<double> mean,
		std::vector<double> stddev)
	: mean(mean)
	, stddev(stddev)
{
	if (mean.size() != 2 || stddev.size() != 2) {
		throw std::invalid_argument("Mean and standard deviation must both be 2 dimensional");
	}
}


void GaussianDataset::generateSamples(int num) {
	int i = data.size();
	data.resize(i + num);

	for (; i < data.size(); i++) {
		data[i] = std::vector<double>(2, 0);
		data[i][0] = box_muller(mean[0], stddev[0]);
		data[i][1] = box_muller(mean[1], stddev[1]);
	}	
}
