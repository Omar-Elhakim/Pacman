#include "Level.h"
#include "Window.h"
#include "mapmaker.h"

int WindowWidth = 800, WindowHeight = 600;
int main() {
    Window window = Window(WindowWidth, WindowHeight, "Mapmaker");
    Level l1 = Level(WindowWidth, WindowHeight);
    mapMaker();
    // l1.notgame();
    return 0;
}
