/*#include "Level.h"
#include "Window.h"
#include "mapmaker.h"

int WindowWidth = 800, WindowHeight = 600;
int main() {
    Window window = Window(WindowWidth, WindowHeight, "Mapmaker");
    Level l1 = Level(WindowWidth, WindowHeight);
    // mapMaker();
    l1.start();
    return 0;
}*/

#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "raylib.h" 
#include "Window.h"
using namespace std;
//using namespace lay;

struct Point {
    int x;
    int y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

class Pacman {
public:
    Point position;
    Pacman(Point pos) : position(pos) {}
};

class Ghost {
public:
    Point position;
    Ghost(Point pos) : position(pos) {}
};

class GameLevel {
private:
    int level;
    vector<Ghost> ghosts;
    Pacman pacman;
    int width;
    int height;
    Window window;

public:
    GameLevel(int _level, int _width, int _height) : level(_level), width(_width), height(_height), window({ 800, 600 }, "Game Window") {
        srand(time(NULL));
        int px = rand() % width;
        int py = rand() % height;
        pacman = Pacman(Point(px, py));

        for (int i = 0; i < level; ++i) {
            int gx = rand() % width;
            int gy = rand() % height;
            ghosts.push_back(Ghost(Point(gx, gy)));
        }


    }

    void update() {
        switch (level) {
        case 1:
            moveGhostsRandomlySlowly();
            break;
        case 2:
            moveGhostsRandomlyFast();
            break;
        case 3:
            moveGhostsTowardsPacman();
            break;
        default:
            cout << "Invalid level!\n";
        }

        int result = multiply(3, 4);
        cout << "Multiplication result: " << result << endl;

        window.display();
    }

    void moveGhostsRandomlySlowly() {
        for (auto& ghost : ghosts) {
            int dx = rand() % 3 - 1;
            int dy = rand() % 3 - 1;
            ghost.position.x += dx;
            ghost.position.y += dy;
        }
    }

    void moveGhostsRandomlyFast() {
        for (auto& ghost : ghosts) {
            int dx = rand() % 3 - 1;
            int dy = rand() % 3 - 1;
            ghost.position.x += 2 * dx;
            ghost.position.y += 2 * dy;
        }
    }

    void moveGhostsTowardsPacman() {
        vector<vector<bool>> visited(height, vector<bool>(width, false));
        queue<Point> q;

        q.push(pacman.position);
        visited[pacman.position.y][pacman.position.x] = true;

        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };

        while (!q.empty()) {
            Point current = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int nx = current.x + dx[i];
                int ny = current.y + dy[i];

                if (nx >= 0 && nx < width && ny >= 0 && ny < height && !visited[ny][nx]) {
                    for (auto& ghost : ghosts) {
                        if (ghost.position.x == nx && ghost.position.y == ny) {
                            ghost.position.x = current.x;
                            ghost.position.y = current.y;
                            break;
                        }
                    }

                    q.push(Point(nx, ny));
                    visited[ny][nx] = true;
                }
            }
        }
    }

    int multiply(int a, int b) {
        return a * b;
    }
};

int main() {
    int width = 10;
    int height = 10;
    GameLevel level1(1, width, height);
    GameLevel level2(2, width, height);
    GameLevel level3(3, width, height);

    for (int i = 0; i < 10; ++i) {
        level1.update();
        level2.update();
        level3.update();
    }

    return 0;
}