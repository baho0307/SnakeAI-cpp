#include "Population.h"
#include "../../main.h"

Population::Population(int size)
{
    snakes = std::vector<Snake>(size);
    //for (int i = 0; i < snakes.size(); i++)
    //    snakes[i] = Snake();
    bestSnake = snakes[0].clone();
    bestSnake.replay = true;
}

bool Population::done()
{
    for (int i = 0; i < snakes.size(); i++) 
    {
        if (!snakes[i].dead)
            return false;
    }
    return true;
}

void Population::update()
{
    if (!bestSnake.dead) 
    {  //if the best snake is not dead update it, this snake is a replay of the best from the past generation
        bestSnake.look();
        bestSnake.think();
        bestSnake.move();
    }
    for (int i = 0; i < snakes.size(); i++) 
    {
        if (!snakes[i].dead) 
        {
            snakes[i].look();
            snakes[i].think();
            snakes[i].move();
        }
    }
}

void Population::show()
{
    bestSnake.show();
}

void Population::setBestSnake()
{
    float max = 0;
    int maxIndex = 0;
    for (int i = 0; i < snakes.size(); i++) 
    {
        if (snakes[i].fitness > max) 
        {
            max = snakes[i].fitness;
            maxIndex = i;
        }
    }
    if (max > bestFitness) 
    {
        bestFitness = max;
        bestSnake = snakes[maxIndex].cloneForReplay();
        bestSnakeScore = snakes[maxIndex].score;
    }
    else 
    {
        bestSnake = bestSnake.cloneForReplay();
        sameBest++;
        if (sameBest > 2) {  //if the best snake has remained the same for more than 3 generations, raise the mutation rate
            mutationRate *= 2;
            sameBest = 0;
        }
    }
}

Snake Population::selectParent()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, fitnessSum);
    float rand = dist(rng);
    float summation = 0;
    for (int i = 0; i < snakes.size(); i++) 
    {
        summation += snakes[i].fitness;
        if (summation > rand)
            return snakes[i];
    }
    return snakes[0];
}

void Population::naturalSelection()
{
    std::vector<Snake> newSnakes = std::vector<Snake>(snakes.size());
    setBestSnake();
    calculateFitnessSum();
    newSnakes[0] = bestSnake.clone().crossover(selectParent());  //add the best snake of the prior generation into the new generation
    newSnakes[0].mutate();
    for (int i = 1; i < snakes.size(); i++) 
    {
        Snake child = selectParent().crossover(selectParent());
        child.mutate();
        newSnakes[i] = child;
    }
    for (int i = 0; i < newSnakes.size(); i++)
        snakes[i] = newSnakes[i].clone();
    //evolution.push_back(bestSnakeScore);
    gen += 1;
}

void Population::mutate()
{
    for (int i = 1; i < snakes.size(); i++)  //start from 1 as to not override the best snake placed in index 0
        snakes[i].mutate();
}

void Population::calculateFitness()
{
    for (int i = 0; i < snakes.size(); i++)
        snakes[i].calculateFitness();
}

void Population::calculateFitnessSum()
{
    fitnessSum = 0;
    for (int i = 0; i < snakes.size(); i++)
        fitnessSum += snakes[i].fitness;
}
