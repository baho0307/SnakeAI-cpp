#pragma once

#include <iostream>
#include <thread>
#include <string>
#include <map>
#include <Windows.h>

struct INFO
{
	int	gen;
	int	highScore;
	int	score;
};

class Map
{
public:
	Map();
	void	Update(INFO inf);
private:
	void	Calc(INFO inf);
	void	Reset();
	void	Swap(); 
	void	setCursorPosition(int x, int y);
	std::string prevBuffer;
	std::string scrBuffer;
	std::map<int, std::string>	texture = 
	{
		{0, " "},		//VOID
		{1, "\xdb"},	//LEFT WALLS
		{10, "\xdb"},	//RIGHT WALLS
		{11, "\xdf"},	//UP WALLS
		{12, "\xdc"},	//DOWN WALLS
		{2, "F"},		//FOOD
		{3, "S"},		//SNEK.
		{4, "@"}		//HEAD
	};
};
