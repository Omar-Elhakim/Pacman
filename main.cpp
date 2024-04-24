#include "Level.h"
#include "Window.h"
#include "mapmaker.h"
#include "FileIO.h"
 
int WindowWidth = 800, WindowHeight = 600;
int main() {
    Window window = Window(WindowWidth, WindowHeight, "Mapmaker");
    Level l1 = Level(WindowWidth, WindowHeight);
    Map myMap;
    int score=10;
    mapMaker();
    FileIO file;
    //file.writeScoreToFile(score);
    file.writeMapToFile(myMap);
    //file.readFromFile();
    file.readMapFromFile();
    l1.start();
   
    return 0;
     
}

