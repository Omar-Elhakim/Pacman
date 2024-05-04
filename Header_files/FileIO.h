#pragma once
#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
void writeScore(int);
void writeMap(Map *map,int n);
vector<int> readScore();
void readMap(Map *map,int n);

