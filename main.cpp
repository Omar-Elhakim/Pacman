//#include "pacman.h"
#include "Game.h"
#include "mapmaker.h"
#include "Window.h"
int main() {
    //game();
    Window window = Window(WindowWidth, WindowHeight, "Mapmaker");
    while (!WindowShouldClose()) {
        BeginDrawing();
        game();
        EndDrawing();
    }
    //Game g(800,600);
    //pacman p;
    //p.f();
    return 0;
}
