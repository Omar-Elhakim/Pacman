#include "FileIO.h"

void FileIO::writeToFile()
{
    int score = 10;
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
