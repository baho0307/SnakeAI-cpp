#pragma once

#include <iostream>
#include <thread>
#include <string>

struct INFO
{
	int	gen;
	int	highScore;
	int	score;
};

class Map
{
public:
	void	Show(INFO inf);
	void	Reset();

private:
	std::string line;
};

