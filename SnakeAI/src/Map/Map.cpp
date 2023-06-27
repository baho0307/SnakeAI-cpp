#include "Map.h"
#include "../../main.h"

void Map::Show()
{
	int	i;
	int	j;

	i = 0;
	line = "";
	while (i < map.size())
	{
		j = 0;
		while (j < map[i].size())
		{
			line += map[i][j] == 1 ? "#" : map[i][j] == 2 ? "F" : map[i][j] == 3 ? "S" : " ";
			j++;
		}
		line += "\n";
		i++;
	}
	std::cout << line;
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
		while (j < 120)
		{
			if (!(i * j) || i == 29 || j == 119)
				map[i].push_back(1);
			else
				map[i].push_back(0);
			j++;
		}
		i++;
	}
}
