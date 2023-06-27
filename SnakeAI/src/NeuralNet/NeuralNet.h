#pragma once

#include "../Matrix/Matrix.h"

class NeuralNet
{
public:
	NeuralNet();
	NeuralNet(int input, int hidden, int output, int hiddenLayers);
	void				mutate(float mr);
	std::vector<float>	output(std::vector<float> inputsArr);
	NeuralNet			crossover(NeuralNet partner);
	NeuralNet			clone();
	void				load(std::vector<Matrix> weight);
	std::vector<Matrix>	pull();

private:
	int	iNodes;
	int	hNodes;
	int	oNodes;
	int	hLayers;

	std::vector<Matrix> weights;
};

