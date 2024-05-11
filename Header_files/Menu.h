#ifndef MENU_H
#define MENU_H
#include "raylib.h"
#include <string>
#include "Level.h"

void mainMenu();
void toStartMenu(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture);
void toHowToPlay(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture);
void toCredits(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture);
void createMap(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture);
void WinScreen(Texture2D background, Font customFont);
void LoseScreen(Texture2D background, Font customFont);
// Custom drawing function
struct CustomButton {
    Rectangle bounds;
    Color color;
    const char* text;
    int fontSize;
};
void DrawCustomButton(CustomButton button);
#endif