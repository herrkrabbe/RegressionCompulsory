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

	Sx = SUM({ 'x' }, points);
	Sy = SUM({ 'y' }, points);
	Sxx = SUM({ 'x', 'x' }, points);
	Syy = SUM({ 'y', 'y' }, points);
	Sxy = SUM({ 'x', 'y' }, points);

	Beta1 = (n * Sxy - Sx * Sy) / (n * Sxx - Sx * Sx);
	Beta0 = (Sy - Beta1 * Sx) / n;
}

void Regression::quadraticLeastSquares(const std::vector<Point>&points, double& a, double& b, double& c) {
    int n = points.size();
    double Sx = 0, Sy = 0, Sxx = 0, Sxxx = 0, Sxxxx = 0, Sxy = 0, Sxxy = 0;

	Sx = SUM({ 'x' }, points);
    Sy = SUM({ 'y' }, points);
    Sxx = SUM({ 'x', 'x'}, points);
	Sxxx = SUM({ 'x', 'x', 'x' }, points);
	Sxxxx = SUM({ 'x', 'x', 'x', 'x' }, points);
	Sxy = SUM({ 'x', 'y' }, points);
	Sxxy = SUM({ 'x', 'x', 'y' }, points);

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
    double a = 0;
    double b = 0;
    double c = 0;

	std::vector<std::vector<Point>> datasets = CreateTestingDataset(subgroup);
    
	linearLeastSquares(datasets[0], c, b);
    double errorLinear = AverageError(datasets[1], a, b, c);
	quadraticLeastSquares(datasets[0], a, b, c);
    double errorQuadratic = AverageError(datasets[1], a, b, c);

	return (errorLinear < errorQuadratic) ? SubgroupDegree{ subgroup, 1 } : SubgroupDegree{ subgroup, 2 };
}

double Regression::SUM(std::vector<xyEnumerator> values, const std::vector<Point>& points)
{
    if (values.size() == 0) {
        throw;
    }
    if (points.size() == 0) {
        throw;
    }

    double sum = 0;
    for (const Point p : points) {
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

double Regression::SUM(std::vector<char> values, const std::vector<Point>& points) {
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

double Regression::AverageError(const std::vector<Point>& subgroup, double a, double b, double c)
{
    double sumError = 0;

	for (Point p : subgroup) {
		double y = a * p.x * p.x + b * p.x + c;
		sumError += abs(p.y - y);
	}

    return sumError/subgroup.size();
}

std::vector<std::vector<Point>> Regression::CreateTestingDataset(std::vector<Point> data)
{   
    int trainingThreshold = 70;
	std::vector<Point> trainingData;
	std::vector<Point> testingData;

	for (Point p : data) {
		int random = rand() % 100;
		if (random < trainingThreshold) {
			trainingData.push_back(p);
		}
		else {
			testingData.push_back(p);
		}
	}

    return {trainingData, testingData};
}
