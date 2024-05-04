#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Map.h"
using namespace std;
class FileIO
{
public:
	void writeScoreToFile(int);
	void writeMapToFile(Map& myMap);
	void readFromFile();
	Map readMapFromFile();
};

