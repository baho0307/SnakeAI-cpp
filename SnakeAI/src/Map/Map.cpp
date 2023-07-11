#include "Map.h"
#include "../../main.h"

void Map::setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

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
			if (!(i + j) || (i == HEIGHT - 1 && j == WIDTH - 1) || (i == 0 && j == WIDTH - 1) || (i == HEIGHT - 1 && j == 0))
				map[i].push_back(1);
			else if (i == 0)
				map[i].push_back(11);
			else if (i == HEIGHT - 1)
				map[i].push_back(12);
			else if (j == 0)
				map[i].push_back(1);
			else if (j == WIDTH - 1)
				map[i].push_back(10);
			else
				map[i].push_back(0);
			j++;
		}
		i++;
	}
}

void Map::Swap()
{
	std::string	tmp;

	tmp = prevBuffer;
	prevBuffer = scrBuffer;
	scrBuffer = tmp;
}

void Map::PrintStats()
{
	setCursorPosition(61, 10);
	std::cout << "    ";
	setCursorPosition(61, 10);
	std::cout << *(info.gen);
	setCursorPosition(61, 11);
	std::cout << "    ";
	setCursorPosition(61, 11);
	std::cout << *(info.highScore);
	setCursorPosition(61, 12);
	std::cout << "    ";
	setCursorPosition(61, 12);
	std::cout << *(info.score);
	setCursorPosition(61, 13);
	std::cout << "    ";
	setCursorPosition(61, 13);
	std::cout << *(info.lifeLeft);
}

void Map::Calc()
{
	int	i;
	int	j;

	i = 0;
	prevBuffer = "";
	while (i < map.size())
	{
		j = 0;
		while (j < map[i].size())
		{
			prevBuffer += texture[map[i][j]];
			j++;
		}
		if (i != map.size() - 1)
			prevBuffer += "\n";
		i++;
	}
	Swap();
	Reset();
}

Map::Map(INFO inf)
{
	info = inf;
	setCursorPosition(47, 10);
	std::cout << "       GEN : ";
	setCursorPosition(47, 11);
	std::cout << " HIGHSCORE : ";
	setCursorPosition(47, 12);
	std::cout << "	    SCORE : ";
	setCursorPosition(47, 13);
	std::cout << "  LIFE LEFT : ";
	Reset();
}

void Map::Update()
{
	Calc();
	if (prevBuffer == "")
	{
		setCursorPosition(0, 0);
		std::cout << scrBuffer;
	}
	else
	{
		for (int i = 0; i < scrBuffer.size(); i++)
		{
			if (scrBuffer[i] != prevBuffer[i])
			{
				setCursorPosition((i % (WIDTH + 1)), (i / (WIDTH + 1)));
				std::cout << scrBuffer[i];
			}
		}
		PrintStats();
		setCursorPosition(0, 0);
	}
}
