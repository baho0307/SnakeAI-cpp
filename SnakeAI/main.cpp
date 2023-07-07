#include "main.h"

int								HEIGHT = 30;
int								WIDTH = 44;
int								hidden_layer = 6;
std::vector<std::vector<int>>	map(HEIGHT, std::vector<int>(WIDTH, 0));
float							mutationRate = 0.1;