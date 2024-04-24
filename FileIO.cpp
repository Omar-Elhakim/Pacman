#include "FileIO.h"
#include "Map.h"
#include "Cell.h"

void FileIO::writeScoreToFile(int score)
{
    
    ofstream outFile("score.txt");
    if (outFile.is_open()) {
        outFile << "Score: " << score << endl;
        outFile.close();
        cout << "Score saved to score.txt" << endl;
    }
    else {
        cout << "Error: Unable to open file for writing!" << endl;
        
    }
}
void FileIO::writeMapToFile(Map& myMap)
{

    ofstream outFile("map.txt");
    if (outFile.is_open()) {
        outFile << "Map: " << myMap.toString() << endl;
        outFile.close();
        cout << "Map saved to map.txt" << endl;
    }
    else {
        cout << "Error: Unable to open file for writing!" << endl;

    }
}

void FileIO::readFromFile()
{
    ifstream inFile("score.txt");
    string line;
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            cout << "Score read from file: " << line << endl;
        }
        inFile.close();
    }
    else {
        cerr << "Error: Unable to open file for reading!" << endl;
        
    }
}
Map FileIO::readMapFromFile() {
    ifstream inFile("map.txt");
    Map myMap;
    int height = hc;
    int width = vc;
    inFile >> height >> width;
    Cell** list{};
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            list[i][j].TileType = ROAD;
            list[i][j].pos.x = j;
            list[i][j].pos.y = i;
            if (isEven(i + j)) {
                list[i][j].BackgroundColor = BROWN;
            }
            else
                list[i][j].BackgroundColor = WHITE;
        }
    }
    inFile.close();
    return myMap;
}
