#include "../Header_files/Level.h"
#include <vector>

Level::Level(int WindowWidth, int WindowHeight, int n,int l) : WindowWidth(WindowWidth), WindowHeight(WindowHeight), n(n),l(l) {
    map = new Map();
    if (n != 4) {
        readMap(map, n);
        map->ColorMap();
    }
    food = new Food(map);
    pacman = new Pacman(map, food);
    if(l==1) ghost = new Ghost(map,0.4);
    else  ghost = new Ghost(map, 0.8);
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
    ghost->InitialPosition[0] = map->getClPos({ 10,10 });
    if (l != 3) {
    for (int i = 0; i < 4; i++) to.push_back(GetRandomCl(map));
}

    while (!WindowShouldClose()) {
        pacmanCenter = { pacman->InitialPosition.x + map->CellWidth / 2,
                               pacman->InitialPosition.y + map->CellHeight / 2 };
        BeginDrawing();
        ClearBackground(BLACK);
        map->Draw();
        food->draw(map);
        pacman->draw();
        ghost->draw();
        if (startc == 0) PlaySound(startsound);
        startc++;
        if (l != 3) {
            for (int i = 0; i < 4; i++) {
                ghostCenter = { ghost->InitialPosition[i].x + map->CellWidth / 2,
                               ghost->InitialPosition[i].y + map->CellHeight / 2 + 10 };

                path = map->FindPath(map->getClArrPos(ghostCenter), to[i]);
                while (path.size() <= 2){ 
                    to[i] = GetRandomCl(map);
                path = map->FindPath(map->getClArrPos(ghostCenter), to[i]);
                }
                if (map->posInGameCanvas(pacmanCenter)) {
                    if (map->FindPath(map->getClArrPos(ghostCenter), map->getClArrPos(pacmanCenter)).size() == 1) {
                        StopSound(startsound);
                        writeScore(pacman->score);
                        return 0;
                    }
                }
                nextcellCenter = { map->getClPos(path[1]).x + map->CellWidth / 2,
                               map->getClPos(path[1]).y + map->CellHeight / 2 };
                ghostCenter = { ghost->InitialPosition[i].x + map->CellWidth / 2,
                               ghost->InitialPosition[i].y + map->CellHeight / 2 };
                path = map->FindPath(map->getClArrPos(ghostCenter), to[i]);
                nextcellCenter = { map->getClPos(path[1]).x + map->CellWidth / 2,
                               map->getClPos(path[1]).y + map->CellHeight / 2 };
                relativePos.x = ghostCenter.x - nextcellCenter.x;
                relativePos.y = ghostCenter.y - nextcellCenter.y;
                if (relativePos.y >= 1)       ghost->goUp(i);//it's on top of it
                else if (relativePos.y <= -1) ghost->goDown(i);
                if (relativePos.x >= 1)       ghost->goLeft(i);//it's in the same column, let's see the difference in rows
                else if (relativePos.x <= -1) ghost->goRight(i); //it's in the same column, let's see the difference in rows
            }
        }
        else if (map->posInGameCanvas(pacmanCenter)) {
            for (int i = 0; i < 4; i++) {
                ghostCenter = { ghost->InitialPosition[i].x + map->CellWidth / 2,
                               ghost->InitialPosition[i].y + map->CellHeight / 2  };
                path = map->FindPath(map->getClArrPos(ghostCenter), map->getClArrPos(pacmanCenter));
                if (path.size() == 1) {
                    StopSound(startsound);
                    writeScore(pacman->score);
                    return 0;
                }
                nextcellCenter = { map->getClPos(path[1]).x + map->CellWidth / 2,
                               map->getClPos(path[1]).y + map->CellHeight / 2 };
               ghostCenter = { ghost->InitialPosition[i].x + map->CellWidth / 2,
                               ghost->InitialPosition[i].y + map->CellHeight / 2 };
                path = map->FindPath(map->getClArrPos(ghostCenter), map->getClArrPos(pacmanCenter));
                nextcellCenter = { map->getClPos(path[1]).x + map->CellWidth / 2,
                               map->getClPos(path[1]).y + map->CellHeight / 2 };
                relativePos.x = ghostCenter.x - nextcellCenter.x;
                relativePos.y = ghostCenter.y - nextcellCenter.y;
                if (relativePos.y >= 1)       ghost->goUp(i);//it's on top of it
                else if (relativePos.y <= -1) ghost->goDown(i);
                if (relativePos.x >= 1)       ghost->goLeft(i);//it's in the same column, let's see the difference in rows
                else if (relativePos.x <= -1) ghost->goRight(i); //it's in the same column, let's see the difference in rows
            }
        }
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
            for (int i = 0; i < 4; i++) ghost->InitialPosition[i] = map->getClPos(GetRandomCl(map));
            // writeMap(map,3);
            food->update(map);
        }
        if (IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_ESCAPE)) {
            StopSound(startsound);
            writeScore(pacman->score);
            return 0;
        }
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
        if (pacman->score == food->count * 10 || IsKeyPressed(KEY_Y)) {
            StopSound(startsound);
            writeScore(pacman->score);
            return 1;
        }
        EndDrawing();
    }
    return 0;
}


int Level::ghostsMovement(int l){
    if (l == 3) {
        for (int i = 0; i < 4; i++) {
            pacmanCenter = { pacman->InitialPosition.x + map->CellWidth / 2,
                           pacman->InitialPosition.y + map->CellHeight / 2 };
            ghostCenter = { ghost->InitialPosition[i].x + map->CellWidth / 2,
                           ghost->InitialPosition[i].y + map->CellHeight / 2 + 10 };
            //Vector2i to = GetRandomCl(map);
            //cout << to.x << "\t" << to.y;
            path = map->FindPath(map->getClArrPos(ghostCenter), map->getClArrPos(pacmanCenter));
            if (path.size() == 1) return 1;
            nextcellCenter = { map->getClPos(path[1]).x + map->CellWidth / 2,
                           map->getClPos(path[1]).y + map->CellHeight / 2 };
            pacmanCenter = { pacman->InitialPosition.x + map->CellWidth / 2,
                           pacman->InitialPosition.y + map->CellHeight / 2 };
            ghostCenter = { ghost->InitialPosition[i].x + map->CellWidth / 2,
                           ghost->InitialPosition[i].y + map->CellHeight / 2 };
            path = map->FindPath(map->getClArrPos(ghostCenter), map->getClArrPos(pacmanCenter));
            nextcellCenter = { map->getClPos(path[1]).x + map->CellWidth / 2,
                           map->getClPos(path[1]).y + map->CellHeight / 2 };
            relativePos.x = ghostCenter.x - nextcellCenter.x;
            relativePos.y = ghostCenter.y - nextcellCenter.y;
            if (relativePos.y >= 1)       ghost->goUp(i);//it's on top of it
            else if (relativePos.y <= -1) ghost->goDown(i);
            if (relativePos.x >= 1)       ghost->goLeft(i);//it's in the same column, let's see the difference in rows
            else if (relativePos.x <= -1) ghost->goRight(i); //it's in the same column, let's see the difference in rows
        }
    }
}