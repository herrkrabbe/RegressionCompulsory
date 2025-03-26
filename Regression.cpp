#include "Regression.h"

std::vector<std::vector<Point>> Regression::SimpleParser(const std::vector<Point>& data)
{
	std::vector<std::vector<Point>> subgroupList;
	std::vector<Point> subgroup;
    double largestSlope = 0;
    double previousSlope = 0;
    Point previousPoint{ 0, 0 };
    

    for (Point p : data) {
        //first subgroup
        if (subgroup.size() == 0) {
            subgroup.push_back(p);
            previousPoint = p;
            continue;
        }


        //calculate slope
		double slope = (p.y - previousPoint.y) / (p.x - previousPoint.x);

        //check slope
        if
        (
            ( abs(slope) > (abs(largestSlope) * 3 ) )
            &&
            ( subgroup.size() > 3 )
        ) 
        {  
            //start new subgroup
			subgroupList.push_back(subgroup);
			subgroup.clear();
			subgroup.push_back(p);
            previousPoint = p;

            largestSlope = 0;
            previousSlope = 0;
            continue;
        }

        //extend current subgroup
        previousSlope = slope;
		largestSlope = (abs(slope) > abs(largestSlope)) ? slope : largestSlope;
		subgroup.push_back(p);
		previousPoint = p;
    }
    subgroupList.push_back(subgroup);
    return subgroupList;
}

void Regression::linearLeastSquares(const std::vector<Point>& points, double& Beta0, double& Beta1) {
    int n = points.size();
    double Sx = 0, Sy = 0, Sxx = 0, Sxy = 0, Syy = 0;

    for (const Point p : points) {
        Sx += p.x;
        Sy += p.y;
        Sxx += (p.x) * (p.x);
        Syy += (p.y) * (p.y);
        Sxy += (p.x) * (p.y);
    }

	Beta1 = (n * Sxy - Sx * Sy) / (n * Sxx - Sx * Sx);
	Beta0 = (Sy - Beta1 * Sx) / n;
}

void Regression::quadraticLeastSquares(const std::vector<Point>&points, double& a, double& b, double& c) {
    int n = points.size();
    double Sx = 0, Sy = 0, Sxx = 0, Sxxx = 0, Sxxxx = 0, Sxy = 0, Sxxy = 0;

    for (const auto& p : points) {
        Sx += p.x;
        Sy += p.y;
        Sxx += p.x * p.x;
        Sxxx += p.x * p.x * p.x;
        Sxxxx += p.x * p.x * p.x * p.x;
        Sxy += p.x * p.y;
        Sxxy += p.x * p.x * p.y;
    }

    // Solve using Eigen for Ax = B (Matrix Form)
    Eigen::Matrix3d A;
    Eigen::Vector3d B, X;

    A << Sxxxx, Sxxx, Sxx,
        Sxxx, Sxx, Sx,
        Sxx, Sx, n;

    B << Sxxy, Sxy, Sy;

    X = A.colPivHouseholderQr().solve(B);
    a = X(0);
    b = X(1);
    c = X(2);
}

SubgroupDegree Regression::BestFitDegree(const std::vector<Point>& subgroup)
{
    return SubgroupDegree();
}

double Regression::SUM(std::vector<xyEnumerator> values, std::vector<Point> points)
{
    if (values.size() == 0) {
        throw;
    }
    if (points.size() == 0) {
        return 0;
    }

    double sum = 0;
    for (Point p : points) {
        double term = 1;
        for (xyEnumerator val : values) {
            switch (val) {
            case xyEnumerator::x:
                term *= p.x;
                break;
            case xyEnumerator::y:
                term *= p.y;
                break;
            }
            
        }
        sum += term;
    }
    return sum;
}

double Regression::SUM(std::vector<char> values, std::vector<Point> points) {
    std::vector<xyEnumerator> xyValues;
	for (char val : values) {
        switch (val) {
		case 'x':
			xyValues.push_back(xyEnumerator::x);
			break;
        case 'y':
			xyValues.push_back(xyEnumerator::y);
			break;
        default:
            throw;
            break;
        }
	}
    return SUM(xyValues, points);
}

double Regression::AverageError(std::vector<Point>& subdomain, double a, double b, double c)
{
    double sumError = 0;

	for (Point p : subdomain) {
		double y = a * p.x * p.x + b * p.x + c;
		sumError += abs(p.y - y);
	}

    return sumError/subdomain.size();
}
