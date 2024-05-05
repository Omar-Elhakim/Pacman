#include "../Header_files/Window.h"
#include "../Header_files/Menu.h"

int WindowWidth = GetScreenWidth(), WindowHeight = GetScreenHeight();

int main() {
    Window window = Window(WindowWidth, WindowHeight, "Pac-Man");
    mainMenu();
    return 0;
}