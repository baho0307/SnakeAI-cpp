#pragma once

#include "Food.h"
#include"../../main.h"

Food::Food()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> disty(2, HEIGHT - 3);
    std::uniform_int_distribution<std::mt19937::result_type> distx(2, WIDTH - 3);

    x = distx(dev);
    y = disty(dev);
}

void Food::Show()
{
    map[y][x] = 2;
}

Food Food::Clone()
{
    Food f = Food();
    f.x = x;
    f.y = y;
    return f;
}
