#include "../Header_files/Level.h"
#include "../Header_files/Window.h"
#include "../Header_files/mapmaker.h"
#include "../DifficultyLevels.h"
#include "../Ghost.h"

int WindowWidth = 800, WindowHeight = 600;
int main() {
    Window window = Window(WindowWidth, WindowHeight, "Mapmaker");
    Level l1 = Level(WindowWidth, WindowHeight);
    // mapMaker();
    l1.start();

    return 0;
}
