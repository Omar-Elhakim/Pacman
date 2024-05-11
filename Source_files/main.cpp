#include "../Header_files/Menu.h"
#include "../Header_files/Window.h"

int WindowWidth = 800, WindowHeight = 600;

int main() {
    Window window = Window(WindowWidth, WindowHeight, "Pac-Man");
    mainMenu();
    return 0;
}
