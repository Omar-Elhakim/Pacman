#include "../Header_files/Menu.h"
#include "../Header_files/Window.h"
#include <raylib.h>

int WindowWidth = 800, WindowHeight = 600;

int main() {
    Window window = Window(WindowWidth, WindowHeight, "Pac-Man");
    Level level = Level(GetScreenWidth(), GetScreenHeight(), 1, 1);
    level.start();
    // mainMenu();
    return 0;
}
