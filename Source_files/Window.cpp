#include "../Header_files/Window.h"
#include "raylib.h"

Window::Window(int Width, int Height, const char *title) {
    this->Width = Width;
    this->Height = Height;
    color = BLACK;
    SetTraceLogLevel(LOG_NONE);
    InitWindow(Width, Height, title);
    // Initialize audio device
    InitAudioDevice();
    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    Image icon = LoadImage("assets/icon.png");
    // Set custom icon for the window
    SetWindowIcon(icon);
    // Unload the icon image from memory
    UnloadImage(icon);
}

Window::~Window() {
    CloseAudioDevice();
    CloseWindow();
}
