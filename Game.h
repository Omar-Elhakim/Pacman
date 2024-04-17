#ifndef GAME_H
#define GAME_H
#pragma once

class Game
{
public:
    Game(int WindowWidth,int WindowHeight);
    int WindowWidth, WindowHeight;
    CellList *cellLst = nullptr;
    ~Game();

private:

};

#endif