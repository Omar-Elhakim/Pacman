#pragma once
#include "Map.h"

class Food {
	int centerx=0;
	int centery=0;
	
public:
	float FRadius = 5.0f;
	Food(Map* map);
	//~Food();
	void draw(Map* map);
	void update(Map* map);
	int count;
};