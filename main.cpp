#include "Level.h"
#include "Window.h"
#include "mapmaker.h"
#include "FileIO.h"

int WindowWidth = 800, WindowHeight = 600;
int main() {
    Window window = Window(WindowWidth, WindowHeight, "Mapmaker");
    Level l1 = Level(WindowWidth, WindowHeight);
    // mapMaker();
    l1.start();
    FileIO file;
    file.writeToFile();
    file.readFromFile();
    return 0;
     
}

