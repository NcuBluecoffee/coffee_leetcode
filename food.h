#pragma once

#include <iostream>
#include "wall.h"

using namespace std;

class Food {
public:
	Food(Wall & tempWall);

	//…Ë÷√ ≥ŒÔ
	void setFood();

	int foodX;
	int foodY;

	Wall & wall;
};