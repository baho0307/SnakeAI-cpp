#pragma once

#include <vector>
#include <random>
#include <omp.h>
#include "../Snake/Snake.h"

class Population
{
public:
	Snake	bestSnake;
	int		gen = 0;
	int		bestSnakeScore = 0;

	Population(int size);
	bool	done();
	void	update();
	void	show();
	void	setBestSnake();
	Snake	selectParent();
	void	naturalSelection();
	void	mutate();
	void	calculateFitness();
	void	calculateFitnessSum();

private:
	std::vector<Snake>	snakes;
	
	int					sameBest = 0;

	float				bestFitness = 0;
	float				fitnessSum = 0;

};

