#pragma once
#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include "Point.h"

namespace Regression {
	std::vector<std::vector<Point>> SimpleParser(std::vector<Point> points);

	void linearLeastSquares(const std::vector<Point>& points, double& Beta0, double& Beta1);

	void quadraticLeastSquares(const std::vector<Point>& points, double& a, double& b, double& c);
}
