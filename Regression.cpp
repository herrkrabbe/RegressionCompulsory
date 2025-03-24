#include "Regression.h"

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

    //Beta0 = // complete the code
    //Beta1 = // complete the code
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