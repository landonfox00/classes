/*
 * dataset.h
 *
 * Used to generate random samples from a 2D Gaussian Distribution
 * x and y are assumed to be independent
 *
 * Author: Logan Leavitt
 *
 */

#ifndef _GAUSSIANDATASET_H
#define _GAUSSIANDATASET_H

#include <vector>


class GaussianDataset {
public:

	GaussianDataset(std::vector<double> mean,
			std::vector<double> stddev);

	void generateSamples(int num);

	std::vector<std::vector<double>> data;

private:
	std::vector<double> mean;
	std::vector<double> stddev;

};



#endif // _GAUSSIANDATASET_H
