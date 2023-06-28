#include "Map.h"
#include "../../main.h"

void Map::Show()
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
		line += "\n";
		i++;
	}
	j = 0;
	while (j < map[i].size())
	{
		line += map[i][j] == 1 ? "#" : map[i][j] == 2 ? "F" : map[i][j] == 3 ? "S" : map[i][j] == 4 ? "@" : " ";
		j++;
	}
	std::cout << line;
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(10ms);
}

void Map::Reset()
{
	int	i;
	int	j;

	map.clear();
	i = 0;
	while (i < 30)
	{
		j = 0;
		map.push_back(std::vector<int>());
		while (j < 44)
		{
			if (!(i * j) || i == 29 || j == 43)
				map[i].push_back(1);
			else
				map[i].push_back(0);
			j++;
		}
		i++;
	}
}
