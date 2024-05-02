//#include "../Header_files/Level.h"
//#include "../Header_files/Window.h"

#include <string>
#include <iostream>
#include "raylib.h"
using namespace std;
int WindowWidth = 800, WindowHeight = 600;
const int screenWidth = 800;
const int screenHeight = 600;
int currentScreen = 0; // 0 - Start Menu, 1 - Easy Menu, etc.
// Menu functions
void mainMenu(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture);

void toStartMenu(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture);
void toHowToPlay(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture);
void toCredits(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture);
int main() {
    InitWindow(screenWidth, screenHeight, "Pac-Man");
    SetTargetFPS(60);
    // Initialize audio device
    InitAudioDevice();

    // Load background music
    Music backgroundMusic = LoadMusicStream("assets/background_music.mp3");

    // Start playing the background music
    PlayMusicStream(backgroundMusic);

    // Set the volume of the background music to 30% (0.3)
    SetMusicVolume(backgroundMusic, 0.3);

    // Load custom icon image
    Image icon = LoadImage("assets/icon.png");

    // Set custom icon for the window
    SetWindowIcon(icon);

    // Unload the icon image from memory
    UnloadImage(icon);

    // Load common resources
    Texture2D background = LoadTexture("assets/background.png");
    Texture2D logo = LoadTexture("assets/logo.png");
    Font customFont = LoadFont("assets/Itim-Regular.ttf");

    // Arrow button texture
    Texture2D arrowTexture = LoadTexture("assets/arrow.png");

    // Start with the main menu
    mainMenu(background, logo, customFont, arrowTexture);

    // Unload common resources
    UnloadFont(customFont);
    UnloadTexture(logo);
    UnloadTexture(background);
    UnloadTexture(arrowTexture);

    // Stop and unload the background music
    StopMusicStream(backgroundMusic);
    UnloadMusicStream(backgroundMusic);
    // Close audio device
    CloseAudioDevice();
    // Close window and exit

    CloseWindow();
    return 0;
}

void mainMenu(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture) {
    // Custom button color (F9C328)
    Color buttonColor = { 249, 195, 40, 255 };
    // Custom button color (ee2327)
    Color buttonColor2 = { 238, 35, 39, 255 };
    Color textColor = BLACK; // Black color for text

    // Main menu variables
    const int NUM_OPTIONS = 4;
    const char* menuOptions[NUM_OPTIONS] = { "START GAME", "HOW TO PLAY", "CREDITS", "QUIT GAME" };
    Rectangle buttons[NUM_OPTIONS];

    // Buttons positions and sizes
    const float buttonWidth = 246; // Width of each button rectangle
    const float buttonHeight = 60; // Height of each button rectangle
    const float buttonSpacing = 20; // Spacing between buttons
    const float startX = 277; // X-position for all buttons
    const float startY = 213; // Y-position for the first button

    buttons[0] = { startX, startY, buttonWidth, buttonHeight };
    buttons[1] = { startX, startY + buttonHeight + buttonSpacing + 10, buttonWidth, buttonHeight };
    buttons[2] = { startX, startY + (buttonHeight + buttonSpacing) * 2, buttonWidth, buttonHeight };
    buttons[3] = { startX, startY + (buttonHeight + buttonSpacing) * 2 + buttonHeight + 32, buttonWidth, buttonHeight };

    while (!WindowShouldClose()) {
        // Main menu logic
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < NUM_OPTIONS; ++i) {
                if (CheckCollisionPointRec(GetMousePosition(), buttons[i])) {
                    switch (i) {
                    case 0: // Start Game button
                        toStartMenu(background, logo, customFont, arrowTexture);
                        break;
                    case 1: // How to play button
                        toHowToPlay(background, logo, customFont, arrowTexture);
                        break;
                    case 2: // Credits button
                        toCredits(background, logo, customFont, arrowTexture);
                        break;
                    case 3: // Quit Game button
                        CloseWindow(); // End the game
                        break;
                    }
                    break; // Exit loop after button press is handled
                }
            }
        }

        BeginDrawing();

        // Draw background image
        DrawTexture(background, 0, 0, WHITE);

        // Draw logo
        DrawTextureRec(logo, { 0, 0, 499, 213 }, { 151, 9 }, WHITE);

        // Draw main menu buttons
        for (int i = 0; i < NUM_OPTIONS; ++i) {
            if (i == 0) {
                DrawRectangleRec(buttons[i], buttonColor2); // using red color for the first button
            }
            else {
                DrawRectangleRec(buttons[i], buttonColor); // Use default color for other buttons
            }

            // passing each button name from the array
            string optionText = menuOptions[i];

            // Calculate text position to center it within the button
            float textX = buttons[i].x + (buttons[i].width - MeasureTextEx(customFont, optionText.c_str(), 36, 0).x) / 2;
            float textY = buttons[i].y + (buttons[i].height - 36) / 2;

            // Draw text with custom font and font size 36
            DrawTextEx(customFont, optionText.c_str(), { textX, textY }, 36, 0, textColor);
        }
        EndDrawing();
    }
}

void toStartMenu(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture) {
    // Custom button color (F9C328)
    Color buttonColor = { 249, 195, 40, 255 };
    Color textColor = WHITE; // White color for text

    // Main menu variables
    const int NUM_LEVELS = 3;
    const char* levelNames[NUM_LEVELS] = { "LEVEL 1", "LEVEL 2", "LEVEL 3" };
    const char* difficultyNames[NUM_LEVELS] = { "EASY :", "MEDIUM :", "HARD :" };
    Rectangle levelButtons[NUM_LEVELS][3];
    Vector2 difficultyTextPos[NUM_LEVELS];

    // Buttons positions and sizes
    const float buttonWidth = 100;
    const float buttonHeight = 20;
    const float buttonSpacingX = 27;
    const float buttonSpacingY = 30;
    const float startX = 265;
    const float startY = 272;
    // Text positions
    const Vector2 easyTextPos = { 116, 261 };
    const Vector2 mediumTextPos = { 91, 311 };
    const Vector2 hardTextPos = { 111, 361 };

    difficultyTextPos[0] = easyTextPos;
    difficultyTextPos[1] = mediumTextPos;
    difficultyTextPos[2] = hardTextPos;

    // Calculate positions for Easy, Medium, and Hard buttons
    for (int i = 0; i < NUM_LEVELS; ++i) {
        for (int j = 0; j < 3; ++j) {
            levelButtons[i][j] = { startX + j * (buttonWidth + buttonSpacingX),
                                   startY + i * (buttonHeight + buttonSpacingY),
                                   buttonWidth, buttonHeight };
        }
    }

    // Arrow button position and size
    const float arrowButtonWidth = 64;
    const float arrowButtonHeight = 64;
    const float arrowButtonX = 55;
    const float arrowButtonY = 504;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            // Go back to main menu
            mainMenu(background, logo, customFont, arrowTexture);
            break;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Check if the arrow button is clicked
            if (CheckCollisionPointRec(GetMousePosition(), { arrowButtonX, arrowButtonY, arrowButtonWidth, arrowButtonHeight })) {
                // Go back to main menu
                mainMenu(background, logo, customFont, arrowTexture);
                break;
            }

            // Check for clicks on level buttons
            for (int i = 0; i < NUM_LEVELS; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (CheckCollisionPointRec(GetMousePosition(), levelButtons[i][j])) {
                        // Handle button clicks for each level
                        switch (i * 3 + j) {
                        case 0:
                            // Handle Level 1 button click
                            // toLevelMenu("Level 1", 1);
                            break;
                        case 1:
                            // Handle Level 2 button click
                            // toLevelMenu("Level 1", 2);
                            break;
                            // Repeat for the rest of the cases
                        case 2:
                            // Handle Level 3 button click
                            // toLevelMenu("Level 1", 3);
                            break;
                        case 3:
                            // Handle Level 4 button click
                            // toLevelMenu("Level 2", 1);
                            break;
                        case 4:
                            // Handle Level 5 button click
                            // toLevelMenu("Level 2", 2);
                            break;
                        case 5:
                            // Handle Level 6 button click
                            // toLevelMenu("Level 2", 3);
                            break;
                        case 6:
                            // Handle Level 7 button click
                            // toLevelMenu("Level 3", 1);
                            break;
                        case 7:
                            // Handle Level 8 button click
                            // toLevelMenu("Level 3", 2);
                            break;
                        case 8:
                            // Handle Level 9 button click
                            // toLevelMenu("Level 3", 3);
                            break;
                        }
                    }
                }
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw background image
        DrawTexture(background, 0, 0, WHITE);

        // Draw logo
        DrawTextureRec(logo, { 0, 0, 499, 213 }, { 151, 9 }, WHITE);

        // Draw difficulty text
        for (int i = 0; i < NUM_LEVELS; ++i) {
            DrawTextEx(customFont, difficultyNames[i], difficultyTextPos[i], 36, 0, textColor);
        }

        // Draw level buttons and text
        for (int i = 0; i < NUM_LEVELS; ++i) {
            for (int j = 0; j < 3; ++j) {
                DrawRectangleRec(levelButtons[i][j], buttonColor);
                // Calculate text position to center it within the button
                float textX = levelButtons[i][j].x + (levelButtons[i][j].width - MeasureTextEx(customFont, levelNames[j], 18, 0).x) / 2;
                float textY = levelButtons[i][j].y + (levelButtons[i][j].height - 18) / 2;
                DrawTextEx(customFont, levelNames[j], { textX, textY }, 18, 0, BLACK);
            }
        }

        // Draw arrow button
        DrawTexture(arrowTexture, arrowButtonX, arrowButtonY, WHITE);

        EndDrawing();
    }
}

void toHowToPlay(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture) {
    // Custom button color (F9C328)
    Color buttonColor = { 249, 195, 40, 255 };

    // How to play text
    string howToPlayText = "HOW TO PLAY PAC-MAN:\n\n"
        "1.OBJECTIVE: NAVIGATE THE MAZE, GOBBLING UP PELLETS WHILE AVOIDING GHOSTS.\n\n"
        "2.CONTROLS: USE ARROW KEYS OR SWIPE GESTURES TO MOVE PAC-MAN.\n\n"
        "3.PELLETS: EAT ALL THE SMALL PELLETS FOR POINTS.\n\n"
        "4.POWER PELLETS: TURN GHOSTS BLUE, EAT THEM FOR EXTRA POINTS.\n\n"
        "5.GHOSTS: AVOID THEM; THEY COST LIVES IF THEY TOUCH PAC-MAN.\n\n"
        "6.FRUIT: BONUS POINTS FOR EATING FRUITS THAT APPEAR.\n\n"
        "7.EXTRA LIVES: EARNED BY REACHING POINT MILESTONES.\n\n"
        "8.MAZE PATTERNS: COMPLEXITY INCREASES AS YOU PROGRESS.\n\n"
        "9.STRATEGY: PLAN MOVES TO AVOID TRAPS.\n\n"
        "10.SCORING: AIM FOR HIGH SCORES!";

    // Calculate text position to match Figma design
    Vector2 textPosition;
    textPosition.x = 39;
    textPosition.y = 150;

    // Arrow button position and size
    const float arrowButtonWidth = 64;
    const float arrowButtonHeight = 64;
    const float arrowButtonX = 55;
    const float arrowButtonY = 504;


    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            // Go back to main menu
            mainMenu(background, logo, customFont, arrowTexture);    // Return to main menu
            break;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Check if the arrow button is clicked
            if (CheckCollisionPointRec(GetMousePosition(), { arrowButtonX, arrowButtonY, arrowButtonWidth, arrowButtonHeight })) {
                // Go back to main menu
                mainMenu(background, logo, customFont, arrowTexture);    // Return to main menu
                break;
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw background image
        DrawTexture(background, 0, 0, WHITE);

        // Draw How to Play text
        DrawTextEx(customFont, howToPlayText.c_str(), textPosition, 24, 0, buttonColor);

        // Draw arrow button
        DrawTexture(arrowTexture, arrowButtonX, arrowButtonY, WHITE);

        EndDrawing();
    }
}

void toCredits(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture) {
    // Custom button color (F9C328)
    Color buttonColor = { 249, 195, 40, 255 };

    // Credits text
    string creditsText = "MADE BY :\n\n"
        "AHMED MOSTAFA \n\n"
        "OMAR HAKIM \n\n"
        "AHMED ESSAM \n\n"
        "OMAR TEBRY \n\n"
        "OSAMA MAHMOUD \n\n"
        "OMAR WATANY \n\n"
        "AHMED ALI ";

    // Calculate text position to center it on the screen
    Vector2 textPosition;
    textPosition.x = (screenWidth - MeasureTextEx(customFont, creditsText.c_str(), 24, 0).x) / 2;
    textPosition.y = (screenHeight - MeasureTextEx(customFont, creditsText.c_str(), 24, 0).y) / 2;

    // Arrow button position and size
    const float arrowButtonWidth = 64;
    const float arrowButtonHeight = 64;
    const float arrowButtonX = 55;
    const float arrowButtonY = 504;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            // Go back to main menu
            mainMenu(background, logo, customFont, arrowTexture);    // Return to main menu
            break;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Check if the arrow button is clicked
            if (CheckCollisionPointRec(GetMousePosition(), { arrowButtonX, arrowButtonY, arrowButtonWidth, arrowButtonHeight })) {
                // Go back to main menu
                mainMenu(background, logo, customFont, arrowTexture);    // Return to main menu
                break;
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw background image
        DrawTexture(background, 0, 0, WHITE);

        // Draw credits text
        DrawTextEx(customFont, creditsText.c_str(), textPosition, 32, 0, buttonColor);

        // Draw arrow button
        DrawTexture(arrowTexture, arrowButtonX, arrowButtonY, WHITE);

        EndDrawing();
    }
}
