#pragma once

#include <vector>
#include "../Food/Food.h"
#include "../PVector/PVector.h"
#include "../NeuralNet/NeuralNet.h"

class Snake
{
public:
	bool				replay = false;
	bool				dead = false;
	NeuralNet			brain;
	int	lifeLeft = 200;
	int	score = 1;
	float	fitness = 0;

	Snake();
	Snake(int layers);
	Snake(std::vector<Food> foods);
	bool				bodyCollide(float x, float y);
	bool				foodCollide(float x, float y);
	bool				wallCollide(float x, float y);
	void				show();
	void				move();
	void				eat();
	void				shiftBody();
	Snake				cloneForReplay();
	Snake				clone();
	Snake				crossover(Snake parent);
	void				mutate();
	void				calculateFitness();
	void				look();
	std::vector<float>	lookInDirection(PVector dir);
	void				think();
	void				moveUp();
	void				moveDown();
	void				moveLeft();
	void				moveRight();

private:
	int	lifeTime = 0;
	int	foodItterate = 0;

	int	xVel;
	int	yVel;
	
	std::vector<float>	vision;
	std::vector<float>	decision;

	int	headX;
	int	headY;

	std::vector<PVector>	body;
	std::vector<Food>		foodList;

	Food		food;

};

