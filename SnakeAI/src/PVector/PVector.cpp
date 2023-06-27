#include "PVector.h"

PVector::PVector(float x, float y)
{
	this->x = x;
	this->y = y;
}

void PVector::add(PVector a)
{
	x += a.x;
	y += a.y;
}
