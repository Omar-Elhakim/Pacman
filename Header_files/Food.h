#pragma once
#include "Map.h"

class Food {
	int centerx=0;
	int centery=0;
public:
	Food(Map* map);
	//~Food();
	void draw(Map* map);
	void update(Map* map);
	int count;
};