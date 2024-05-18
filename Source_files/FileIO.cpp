#include "../Header_files/FileIO.h"

using namespace std;
vector<int> readScore() {
    vector<int> scores;
    ifstream scoresFile("./assets/scores.txt");
    string score;
    for (int i = 0; i < 3; i++) {
        getline(scoresFile, score);
        scores.push_back(stoi(score));
    }
    return scores;
}
void writeScore(int score) {
    vector<int> scores = readScore();
    scores.push_back(score);
    sort(scores.begin(), scores.end(), greater<int>());
    ofstream scoresFile("./assets/scores.txt");
    for (int i = 0; i < 3; i++) {
        scoresFile << scores[i] << endl;
    }
}
void writeMap(Map *map, int n) {

    fstream mapFile;
    mapFile.open(TextFormat("./assets/Maps/map%d.csv", n), ios::out);
    for (int i = 0; i < hc; i++) {
        for (int j = 0; j < vc; j++) {
            mapFile << (map->GetCell({j, i})->TileType == WALL) << ",";
        }
        mapFile << "\n";
    }
}
void readMap(Map *map, int n) {
    ifstream mapFile;
    mapFile.open(TextFormat("./assets/Maps/map%d.csv", n));
    string row;
    for (int i = 0; i < hc; i++) {
        getline(mapFile, row);
        for (int j = 0; j < vc; j++) {
            map->GetCell({j, i})->TileType = ((row[2 * j] - '0') ? WALL : ROAD);
        }
    }
}
