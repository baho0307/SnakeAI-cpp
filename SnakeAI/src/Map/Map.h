//#pragma once
//
//#include <iostream>
//#include <thread>
//#include <string>
//#include <vector>
//#include <Windows.h>
//
//struct INFO
//{
//	int	gen;
//	int	highScore;
//	int	score;
//};
//
//class Map
//{
//public:
//	Map();
//	void	setCursorPosition(int x, int y);
//	void	setConsoleColour(unsigned short colour);
//	void	Calc(INFO inf);
//	void	Show(INFO inf);
//	void	Swap();
//	void	Clear();
//
//private:
//	std::vector<std::vector<int>> screenBuffer;
//	std::vector<std::vector<int>> calcBuffer;
//	std::vector<char> texture = {' ', '#', 'F', 'S', '@'};
//};

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
