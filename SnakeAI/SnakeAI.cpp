#include <iostream>
#include "src/Food/Food.h"
#include "src/Map/Map.h"
#include "SnakeAI.h"

//HEIGHT : 30, WIDTH : 120

int main()
{
	Map		screen = Map();
	screen.Reset();
	int	x;
	Population pop = Population(2000);
	int	highscore;

	while (true)
	{
		screen.Reset();
		if (pop.done()) 
		{
			highscore = pop.bestSnake.score;
			pop.calculateFitness();
			pop.naturalSelection();
		}
		else 
		{
			pop.update();
			pop.show();
		}
		system("cls");
		screen.Show();
	}
}
