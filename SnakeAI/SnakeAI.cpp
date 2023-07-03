#include <iostream>
#include "src/Food/Food.h"
#include "src/Map/Map.h"
#include "SnakeAI.h"

//HEIGHT : 30, WIDTH : 44

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
			pop.show();
			if (!pop.bestSnake.dead)
				screen.Show(INFO{ pop.gen, pop.bestSnakeScore, pop.bestSnake.score });
			pop.update();
		}
	}
}
