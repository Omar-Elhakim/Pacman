#ifndef MENU_H
#define MENU_H
#include "raylib.h"
#include <string>
#include "Level.h"

void mainMenu();
void toStartMenu(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture, Sound backgroundSound);
void toHowToPlay(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture);
void toCredits(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture);
#endif