#pragma once

#include <vector>
#include <iostream>
#include <random>
#include <math.h>
#include <algorithm>

class Matrix
{
private:
	int	rows;
	int	cols;
	std::vector<std::vector<float>>	matrix;

public:
	Matrix();
	Matrix(int r, int c);
	Matrix(std::vector<std::vector<float>> m);
	void output();
	Matrix dot(Matrix n);
	void randomize();
	Matrix singleColumnMatrixFromArray(std::vector<float> arr);
	std::vector<float> toArray();
	Matrix addBias();
	Matrix activate();
	float relu(float x);
	float sigmoid(float x);
	void mutate(float mutationRate);
	Matrix crossover(Matrix partner);
	Matrix clone();
};
