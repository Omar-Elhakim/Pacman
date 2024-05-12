#include "../Header_files/Level.h"
#include <vector>

Level::Level(int WindowWidth, int WindowHeight, int n) : WindowWidth(WindowWidth), WindowHeight(WindowHeight), n(n) {
    map = new Map();
    if (n != 4) {
        readMap(map, n);
        map->ColorMap();
    }
    food = new Food(map);
    pacman = new Pacman(map, food);
    ghost = new Ghost(map);
    startsound = LoadSound("assets/start-game.wav");
    source = {0, 0}, dest = {vc - 1, hc - 1};
}

Level::~Level() {
    delete map;
    delete pacman;
    map = nullptr;
    pacman = nullptr;
    UnloadSound(startsound);
}

bool Level::start() {
    bool mapdrawn = false;
    Vector2 pacmanCenter = {0};
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        map->Draw();
        food->draw(map);
        pacman->draw();
        ghost->draw();
        if (startc == 0) PlaySound(startsound);
        startc++;
        DrawText(TextFormat("Score: %d", pacman->score), 10, map->infoBarHeight / 2 - 10, 30, WHITE);
        if (IsWindowResized()) {
            map->Update();
            pacman->setSize();
            ghost->setSize();
            food->resize();
        }
        if (mapdrawn == false && n == 4) {
            mapMaker(map);
            mapdrawn = true;
            // writeMap(map,3);

            food->update(map);
        }
        if (IsKeyPressed(KEY_Q)) {
            StopSound(startsound);
            writeScore(pacman->score);
            return 0;
        }
        // if (IsKeyPressed(KEY_F)) {
        pacmanCenter = {pacman->InitialPosition.x + map->CellWidth / 2,
                        pacman->InitialPosition.y + map->CellHeight / 2};
        if (map->posInGameCanvas(pacmanCenter))
            map->FindPath(map->getClArrPos({ghost->InitialPosition[0].x + map->CellWidth / 2,
                                            ghost->InitialPosition[0].y + map->CellHeight / 2}),
                          map->getClArrPos(pacmanCenter));
        pacmanCenter = { pacman->InitialPosition.x + map->CellWidth / 2,
                        pacman->InitialPosition.y + map->CellHeight / 2 };
        if (map->posInGameCanvas(pacmanCenter))
            map->FindPath(map->getClArrPos({ ghost->InitialPosition[1].x + map->CellWidth / 2,
                                            ghost->InitialPosition[1].y + map->CellHeight / 2 }),
                map->getClArrPos(pacmanCenter));
        pacmanCenter = { pacman->InitialPosition.x + map->CellWidth / 2,
                        pacman->InitialPosition.y + map->CellHeight / 2 };
        if (map->posInGameCanvas(pacmanCenter))
            map->FindPath(map->getClArrPos({ ghost->InitialPosition[2].x + map->CellWidth / 2,
                                            ghost->InitialPosition[2].y + map->CellHeight / 2 }),
                map->getClArrPos(pacmanCenter));
        pacmanCenter = { pacman->InitialPosition.x + map->CellWidth / 2,
                        pacman->InitialPosition.y + map->CellHeight / 2 };
        if (map->posInGameCanvas(pacmanCenter))
            map->FindPath(map->getClArrPos({ ghost->InitialPosition[3].x + map->CellWidth / 2,
                                            ghost->InitialPosition[3].y + map->CellHeight / 2 }),
                map->getClArrPos(pacmanCenter));

        
           
        // }
        if (IsKeyPressed(KEY_UP) || pacman->direction.y < 0) {
            pacman->goUp();
            pacman->eat();
        }
        if (IsKeyPressed(KEY_DOWN) || pacman->direction.y > 0) {
            pacman->goDown();
            pacman->eat();
        }
        if (IsKeyPressed(KEY_RIGHT) || pacman->direction.x > 0) {
            pacman->goRight();
            pacman->eat();
        }
        if (IsKeyPressed(KEY_LEFT) || pacman->direction.x < 0) {
            pacman->goLeft();
            pacman->eat();
        }
        if (IsKeyPressed(KEY_W)) {
            ghost->goUp();
        }
        if (IsKeyPressed(KEY_A)) {
            ghost->goLeft();
        }
        if (IsKeyPressed(KEY_S)) {
            ghost->goDown();
        }
        if (IsKeyPressed(KEY_D)) {
            ghost->goRight();
        }
        if (pacman->score == food->count * 10 || IsKeyPressed(KEY_Y)) {
            StopSound(startsound);
            writeScore(pacman->score);
            return 1;
        }
        EndDrawing();
    }
}
