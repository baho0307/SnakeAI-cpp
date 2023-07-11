#include <iostream>
#include "src/Food/Food.h"
#include "src/Map/Map.h"
#include "SnakeAI.h"

//HEIGHT : 30, WIDTH : 44

int main()
{
	Population pop = Population(10000);
	Map		screen = Map(INFO{ &pop.gen, &pop.bestSnakeScore, &pop.bestSnake.score, &pop.bestSnake.lifeLeft});
	int	x;
	int	highscore;

	while (true)
	{
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
				screen.Update();
			pop.update();
		}
	}
}
