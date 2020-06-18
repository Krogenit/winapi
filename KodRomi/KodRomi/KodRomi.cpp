
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
ofstream out("out.txt");
const double e = 2.71828182845904523536;
const double eps = 1e-5;
const int m = 3;
double a = 0; double b = 3; double h = 0.1;
double n = (b - a) / h;
vector <vector<double>>  Y1, Y2, Y3, Y4, Y;
vector <double> X;


float DUDX1(double t, double x, double y, double z, int number)
{
	if (number == 0)
		return (0);
	if (number == 1)
		return (t / z);
	if (number == 2)
		return (-t / y);
}
float DUDX1(double t, double x, double y, int number)
{
	if (number == 0)
		return (3 * t / x);
	if (number == 1)
		return (0);
}

float DUDX(double t, double x, double y, double z, int number)
{
	if (number == 0)
		return (x - 2 * y - z);
	if (number == 1)
		return (y - x + z);
	if (number == 2)
		return (x - z);
}

void Runge(double a, double x0, double y0, double z0)
{
	X[0] = a; Y[0][0] = x0; Y[0][1] = y0; Y[0][2] = z0;

	for (int i = 1; i <= n; i++)
	{
		X[i] = a + i*h;
		for (int j = 0; j < m; ++j)
			Y1[i][j] = h*DUDX(X[i - 1], Y[i - 1][0], Y[i - 1][1], Y[i - 1][2], j);
		for (int j = 0; j < m; ++j)
			Y2[i][j] = h*DUDX(X[i - 1] + h / 2.0, Y[i - 1][0] + Y1[i][0] / 2.0, Y[i - 1][1] + Y1[i][1] / 2.0, Y[i - 1][2] + Y1[i][2] / 2.0, j);
		for (int j = 0; j < m; ++j)
			Y3[i][j] = h*DUDX(X[i - 1] + h / 2, Y[i - 1][0] + Y2[i][0] / 2, Y[i - 1][1] + Y2[i][1] / 2, Y[i - 1][2] + Y2[i][2] / 2, j);
		for (int j = 0; j < m; ++j)
			Y4[i][j] = h*DUDX(X[i - 1] + h, Y[i - 1][0] + Y3[i][0], Y[i - 1][1] + Y3[i][1], Y[i - 1][2] + Y3[i][2], j);
		for (int j = 0; j < m; ++j)
			Y[i][j] = Y[i - 1][j] + (Y1[i][j] + 2 * Y2[i][j] + 2 * Y3[i][j] + Y4[i][j]) / 6;
	}
	//	cout << "U(x) = " << Y[i][0] << " x = " << X[i] << endl;

}

void main()
{
	setlocale(LC_ALL, "Russian");
	int k;
	double ytemp1, delta, ynext1, delta1, delta2, ytemp2, ynext2;
	vector <double> F, ytemp, Delta, ynext;
	X.resize(n + 1);
	Y.resize(n + 1);
	Y1.resize(n + 1);
	Y2.resize(n + 1);
	Y3.resize(n + 1);
	Y4.resize(n + 1);
	F.resize(m);
	ytemp.resize(m);
	Delta.resize(m);
	ynext.resize(m);
	for (int i = 0; i < n + 1; ++i)
	{
		Y[i].resize(m);
		Y1[i].resize(m);
		Y2[i].resize(m);
		Y3[i].resize(m);
		Y4[i].resize(m);
	}
	Runge(0, 5, 3, 5); // для линейной из 3
	//Runge(0, 0, 1, 10);

	for (int i = 3; i <= n; i++)
	{
		X[i] = a + i*h;
		k = 0;
		for (int j = 0; j < m; ++j)
			ytemp[j] = Y[i - 1][j] + h / 12 * (23 * DUDX(X[i - 1], Y[i - 1][0], Y[i - 1][1], Y[i - 1][2], j)
			- 16 * DUDX(X[i - 2], Y[i - 2][0], Y[i - 2][1], Y[i - 2][2], j) + 5 * DUDX(X[i - 3], Y[i - 3][0], Y[i - 3][1], Y[i - 3][2], j));
		for (int j = 0; j < m; ++j)
			F[j] = Y[i - 1][j] + h / 24 * (19 * DUDX(X[i - 1], Y[i - 1][0], Y[i - 1][1], Y[i - 1][2], j)
			- 5 * DUDX(X[i - 2], Y[i - 2][0], Y[i - 2][1], Y[i - 2][2], j) + DUDX(X[i - 3], Y[i - 3][0], Y[i - 3][1], Y[i - 3][2], j));

		do
		{
			for (int j = 0; j < m; ++j)
				ynext[j] = h / 24 * (9 * DUDX(X[i], ytemp[0], ytemp[1], ytemp[2], j)) + F[j];
			for (int j = 0; j < m; ++j)
				Delta[j] = abs(ynext[j] - ytemp[j]);

			for (int j = 0; j < m; ++j)
				delta = Delta[j] * Delta[j];
			delta = sqrt(delta);
			for (int j = 0; j < m; ++j)
				ytemp[j] = ynext[j];

			k++;

		} while ((k < 100) && (delta > eps));
		for (int j = 0; j < m; ++j)
			Y[i][j] = Y[i - 1][j] + h / 24 * (9 * DUDX(X[i], ynext[0], ynext[1], ynext[2], j)
			+ 19 * DUDX(X[i - 1], Y[i - 1][0], Y[i - 1][1], Y[i - 1][2], j)
			- 5 * DUDX(X[i - 2], Y[i - 2][0], Y[i - 2][1], Y[i - 2][2], j) + DUDX(X[i - 3], Y[i - 3][0], Y[i - 3][1], Y[i - 3][2], j));

	}

	for (int i = 0; i <= n; ++i)
	{
		cout << "x = " << Y[i][0] << ", \t";
		cout << "  y = " << Y[i][1] << ",\t" << " z = " << Y[i][2] << ",\t" << " t = " << X[i] << endl;
		out << Y[i][0] << " " << Y[i][1] << " " << Y[i][2] << endl;
	}
	//out << endl;
	//for (int i = 0; i <= n; ++i)
	//	out << Y[i][1] << " ";
	system("pause");
}

