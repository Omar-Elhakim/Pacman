#ifndef WINDOW_H
#define WINDOW_H
#include <raylib.h>

class Window {
  public:
    int Width = 800, Height = 600;
    Color color = BLACK;
    Window(int Width, int Height, const char *title);
    ~Window();
};

#endif // WINDOW_H
