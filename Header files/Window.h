#ifndef WINDOW_H
#define WINDOW_H

class Window {
  public:
    int Width = 800, Height = 600;
    Window(int Width, int Height, const char *title);
    ~Window();
};

#endif // WINDOW_H
