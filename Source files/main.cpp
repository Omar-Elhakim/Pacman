#include "../Header files/Level.h"
#include "../Header files/Window.h"
#include "../Header files/mapmaker.h"

int WindowWidth = 800, WindowHeight = 600;
int main() {
    Window window = Window(WindowWidth, WindowHeight, "Mapmaker");
    Level l1 = Level(WindowWidth, WindowHeight);
    // mapMaker();
    l1.start();
    return 0;
}
