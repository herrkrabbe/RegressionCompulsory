#pragma once
#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include "Point.h"
#include "xyEnumerator.h"

namespace Regression {
	std::vector<std::vector<Point>> SimpleParser(std::vector<Point> data);

	void linearLeastSquares(const std::vector<Point>& points, double& Beta0, double& Beta1);

	void quadraticLeastSquares(const std::vector<Point>& points, double& a, double& b, double& c);

	double SUM(std::vector<xyEnumerator> values, std::vector<Point> points);

	double SUM(std::vector<char> values, std::vector<Point> points));
}
