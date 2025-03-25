// Regression.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Point.h"
#include "Regression.h"

int main()
{
    std::cout << "Hello World!\n";
    std::vector<Point> points = { {1.0, 6.948357}, {2.0, 5.730868}, {3.0, 5.623844}, {4.0, 5.961515},
    {5.0, 5.382923}, {6.0, 6.082932}, {7.0, 8.089606}, {8.0, 9.183717},
    {9.0, 10.46526}, {10.0, 13.27128}, {11.0, 15.46829}, {12.0, 18.56714},
    {13.0, 22.42098}, {14.0, 25.24336}, {15.0, 29.63754}, {16.0, 34.91886},
    {17.0, 39.79358}, {18.0, 45.95712}, {19.0, 51.24599}, {20.0, 57.29385},
    {21.0, 65.43282}, {22.0, 71.68711}, {23.0, 79.33376}, {24.0, 86.48763},
    {25.0, 95.22781}, {26.0, 104.2555}, {27.0, 112.7245}, {28.0, 122.9878},
    {29.0, 132.3997}, {30.0, 142.8542}, {31.0, 153.3991}, {32.0, 165.7261},
    {33.0, 176.2933}, {34.0, 187.6711}, {35.0, 200.9113}, {36.0, 212.5896},
    {37.0, 226.4044}, {38.0, 238.8202}, {39.0, 253.0359}, {40.0, 268.0984},
    {41.0, 161.7692}, {42.0, 161.8857}, {43.0, 162.1422}, {44.0, 162.4494},
    {45.0, 162.2607}, {46.0, 163.0401}, {47.0, 163.5697}, {48.0, 164.7286},
    {49.0, 164.7718}, {50.0, 164.1185}, {51.0, 165.562}, {52.0, 165.6075},
    {53.0, 165.8615}, {54.0, 166.9058}, {55.0, 167.5155}, {56.0, 167.8656},
    {57.0, 167.3804}, {58.0, 168.0454}, {59.0, 168.7656}
    };

	std::vector<std::vector<Point>> trends = Regression::SimpleParser(points);

	for (std::vector<Point> section : trends) {
		std::cout << "New Section:" << std::endl;
		for (Point p : section) {
			std::cout << p.x << " " << p.y << std::endl;
		}
		std::cout << std::endl;
	}

    //double A, B, C;
    //Regression::quadraticLeastSquares(trends[0], A, B, C);
    //std::cout << "Best fit curve: y = " << A << "x^2 + " << B << "x + " << C << std::endl;
    //
    //double a, b;
    //Regression::linearLeastSquares(trends[1], a, b);
    //
    //std::cout << "Best fit line: y = " << a << "x + " << b << std::endl;

    

    
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
