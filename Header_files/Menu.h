#ifndef MENU_H
#define MENU_H
#include "raylib.h"
#include <string>
#include "../Header_files/Level.h"

void mainMenu();

void toStartMenu(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture);
void toHowToPlay(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture);
void toCredits(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture);
#endif