#include "Level.h"
#include "Window.h"
#include "mapmaker.h"

int WindowWidth = 800, WindowHeight = 600;
int main() {
    Window window = Window(WindowWidth, WindowHeight, "Mapmaker");
    //mapMaker();
    //Draw your map with your then press "q" to play on it
    Level l1 = Level(WindowWidth, WindowHeight, mapMaker());
    l1.StartGame();
    return 0;
}
