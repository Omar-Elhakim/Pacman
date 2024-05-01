#include "../Header_files/Window.h"
#include "raylib.h"

Window::Window(int Width, int Height, const char *title) {
    this->Width = Width;
    this->Height = Height;
    color = BLACK;
    SetTraceLogLevel(LOG_NONE);
    InitWindow(Width, Height, title);
    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
}

Window::~Window() {
    CloseWindow();
}
