#include "../Header_files/Level.h"
#include "../Header_files/Window.h"

int WindowWidth = 800, WindowHeight = 600;
int main() {
    Window window = Window(WindowWidth, WindowHeight, "Mapmaker");
    Level l1 = Level(WindowWidth, WindowHeight);
    l1.start();
    return 0;
}
