#include "Map.h"
#include "../../main.h"

//DOUBLE BUFFERING WILL BE ADDED (I HOPE)

//void Map::setCursorPosition(int x, int y)
//{
//	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//	std::cout.flush();
//	COORD coord = { (SHORT)x, (SHORT)y };
//	SetConsoleCursorPosition(hOut, coord);
//}
//
//void Map::setConsoleColour(unsigned short colour)
//{
//	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//	std::cout.flush();
//	SetConsoleTextAttribute(hOut, colour);
//}
//
//void Map::Calc(INFO inf)
//{
//	calcBuffer = map;
//}
//
//Map::Map()
//{
//	screenBuffer = map;
//	calcBuffer = map;
//}
//
//void Map::Show(INFO inf)
//{
//	Calc(inf);
//	Swap();
//	for (int i = 0; i < HEIGHT - 1; i++)
//	{
//		for (int j = 0; j < WIDTH - 1; j++)
//		{
//			if (screenBuffer[i][j] != calcBuffer[i][j])
//			{
//				setCursorPosition(i, j);
//				std::cout << texture[screenBuffer[i][j]];
//			}
//		}
//	}
//}
//
//void Map::Swap()
//{
//	std::vector<std::vector<int>>	tmp;
//
//	tmp = screenBuffer;
//	screenBuffer = calcBuffer;
//	calcBuffer = tmp;
//}
//
//void Map::Clear()
//{
//	screenBuffer = map;
//	calcBuffer = map;
//}
#include "Map.h"
#include "../../main.h"

void Map::Reset()
{
	int	i;
	int	j;

	map.clear();
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		map.push_back(std::vector<int>());
		while (j < WIDTH)
		{
			if (!(i * j) || i == HEIGHT - 1 || j == WIDTH - 1)
				map[i].push_back(1);
			else
				map[i].push_back(0);
			j++;
		}
		i++;
	}
}

void Map::Show(INFO inf)
{
	int	i;
	int	j;

	i = 0;
	line = "";
	while (i < map.size() - 1)
	{
		j = 0;
		while (j < map[i].size())
		{
			line += map[i][j] == 1 ? "#" : map[i][j] == 2 ? "F" : map[i][j] == 3 ? "S" : map[i][j] == 4 ? "@" : " ";
			j++;
		}
		switch (i)
		{
		case 2:
			line += "           GEN : " + std::to_string(inf.gen);
			break;
		case 3:
			line += "     HIGHSCORE : " + std::to_string(inf.highScore);
			break;
		case 4:
			line += "         SCORE : " + std::to_string(inf.score);
			break;
		case 5:
			line += "        M_RATE : " + std::to_string(mutationRate * 100);
			break;
		};
		line += "\n";
		i++;
	}
	j = 0;
	while (j < map[i].size())
	{
		line += map[i][j] == 1 ? "#" : map[i][j] == 2 ? "F" : map[i][j] == 3 ? "S" : map[i][j] == 4 ? "@" : " ";
		j++;
	}
	system("cls");
	std::cout << line;
	using namespace std::chrono_literals;
	Reset();
}


