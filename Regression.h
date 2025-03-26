#pragma once
#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include "Point.h"
#include "xyEnumerator.h"
#include "SubgroupDegree.h"

namespace Regression {
	std::vector<std::vector<Point>> SimpleParser(const std::vector<Point>& data);

	void linearLeastSquares(const std::vector<Point>& points, double& Beta0, double& Beta1);

	void quadraticLeastSquares(const std::vector<Point>& points, double& a, double& b, double& c);

	SubgroupDegree BestFitDegree(const std::vector<Point>& subgroup);

	double SUM(std::vector<xyEnumerator> values, const std::vector<Point>& points);

	double SUM(std::vector<char> values, const std::vector<Point>& points);

	double AverageError(const std::vector<Point>& subgroup, double a, double b, double c);

	/*
	* Function takes a dataset, and separates it into a training and testing dataset.
	* The 0 return index is the trainind data, and the 1 index is the testing data.
	*/
	std::vector<std::vector<Point>> CreateTestingDataset(std::vector<Point> data);
}
