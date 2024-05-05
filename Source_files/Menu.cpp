#include "../Header_files/Menu.h"
#include "raylib.h"


#include "raylib.h"

void mainMenu() {
    // Load background music
    Music backgroundMusic = LoadMusicStream("assets/background_music.mp3");
    PlayMusicStream(backgroundMusic);
    SetMusicVolume(backgroundMusic, 0.3);

    // Load common resources
    Texture2D background = LoadTexture("assets/background.png");
    Texture2D logo = LoadTexture("assets/logo.png");
    Font customFont = LoadFont("assets/Itim-Regular.ttf");
    Texture2D arrowTexture = LoadTexture("assets/arrow.png");

    // Custom button color
    Color buttonColor = { 249, 195, 40, 255 };
    Color buttonColor2 = { 238, 35, 39, 255 };
    Color textColor = BLACK;

    // Main menu variables
    const int NUM_OPTIONS = 4;
    const char* menuOptions[NUM_OPTIONS] = { "START GAME", "HOW TO PLAY", "CREDITS", "QUIT GAME" };
    Rectangle buttons[NUM_OPTIONS];

    // Calculate button positions and sizes based on screen dimensions
    const float screenWidth = GetScreenWidth();
    const float screenHeight = GetScreenHeight();
    const float buttonWidth = screenWidth * 0.4f;
    const float buttonHeight = 60;
    const float buttonSpacing = 20;
    const float startX = (screenWidth - buttonWidth) / 2;
    const float startY = (screenHeight - (NUM_OPTIONS * buttonHeight + (NUM_OPTIONS - 1) * buttonSpacing)) / 2;

    for (int i = 0; i < NUM_OPTIONS; ++i) {
        buttons[i] = { startX, startY + i * (buttonHeight + buttonSpacing), buttonWidth, buttonHeight };
    }

    while (!WindowShouldClose()) {
        // Check for mouse input
        Vector2 mousePos = GetMousePosition();

        for (int i = 0; i < NUM_OPTIONS; ++i) {
            // Check if mouse is hovering over the button
            if (CheckCollisionPointRec(mousePos, buttons[i])) {
                // Check if mouse button is pressed
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    switch (i) {
                    case 0: toStartMenu(background, logo, customFont, arrowTexture); break;
                    case 1: toHowToPlay(background, logo, customFont, arrowTexture); break;
                    case 2: toCredits(background, logo, customFont, arrowTexture); break;
                    case 3: return;
                    }
                }
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw background image
        DrawTexturePro(background, { 0.0f, 0.0f, (float)background.width, (float)background.height },
            { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() }, { 0.0f, 0.0f }, 0.0f, WHITE);

        // Draw logo centered horizontally and vertically
        DrawTexture(logo, (GetScreenWidth() - logo.width) / 2, 70, WHITE);

        // Draw main menu buttons
        for (int i = 0; i < NUM_OPTIONS; ++i) {
            DrawRectangleRec(buttons[i], (i == 0) ? buttonColor2 : buttonColor);

            // Draw text centered within the button
            DrawTextEx(customFont, menuOptions[i],
                { buttons[i].x + (buttons[i].width - MeasureText(menuOptions[i], 36)) / 2,
                buttons[i].y + (buttons[i].height - 36) / 2 }, 36, 0, textColor);
        }

        EndDrawing();
    }

    // Unload resources
    UnloadFont(customFont);
    UnloadTexture(logo);
    UnloadTexture(background);
    UnloadTexture(arrowTexture);

    // Stop and unload background music
    StopMusicStream(backgroundMusic);
    UnloadMusicStream(backgroundMusic);
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

    // Calculate button positions and sizes based on screen dimensions
    const float screenWidth = GetScreenWidth();
    const float screenHeight = GetScreenHeight();
    const float buttonWidth = screenWidth * 0.15f;
    const float buttonHeight = screenHeight * 0.05f;
    const float buttonSpacingX = screenWidth * 0.02f;
    const float buttonSpacingY = screenHeight * 0.05f;
    const float startY = (screenHeight - (NUM_LEVELS * (buttonHeight + buttonSpacingY))) / 2.0f + 50; // Adjust startY to center buttons vertically

    // Text positions
    const float textOffsetY = buttonHeight * 0.25f; // Adjust the offset to center the text vertically within the button
    const Vector2 easyTextPos = { screenWidth * 0.15f + 50, startY + textOffsetY }; // Shifting down by 50 pixels and aligning with button
    const Vector2 mediumTextPos = { screenWidth * 0.15f + 50, startY + buttonHeight + buttonSpacingY + textOffsetY }; // Shifting down by 50 pixels and aligning with button
    const Vector2 hardTextPos = { screenWidth * 0.15f + 50, startY + 2 * (buttonHeight + buttonSpacingY) + textOffsetY }; // Shifting down by 50 pixels and aligning with button

    difficultyTextPos[0] = easyTextPos;
    difficultyTextPos[1] = mediumTextPos;
    difficultyTextPos[2] = hardTextPos;

    // Calculate positions for Easy, Medium, and Hard buttons
    for (int i = 0; i < NUM_LEVELS; ++i) {
        for (int j = 0; j < 3; ++j) {
            levelButtons[i][j] = { (screenWidth - (3 * (buttonWidth + buttonSpacingX))) / 2 + j * (buttonWidth + buttonSpacingX),
                                   startY + i * (buttonHeight + buttonSpacingY),
                                   buttonWidth, buttonHeight };
        }
    }

    // Arrow button position and size
    const float arrowButtonWidth = screenWidth * 0.1f;
    const float arrowButtonHeight = screenHeight * 0.1f;
    const float arrowButtonX = screenWidth * 0.05f + 50; // Shifted right by 50 pixels
    const float arrowButtonY = screenHeight * 0.8f + 50; // Shifting down by 50 pixels

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            // Go back to main menu
            return;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Check if the arrow button is clicked
            if (CheckCollisionPointRec(GetMousePosition(), { arrowButtonX, arrowButtonY, arrowButtonWidth, arrowButtonHeight })) {
                // Go back to main menu
                return;
            }

            // Check for clicks on level buttons
            for (int i = 0; i < NUM_LEVELS; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (CheckCollisionPointRec(GetMousePosition(), levelButtons[i][j])) {
                        // Handle button clicks for each level
                        Level* level;
                        switch (i * 3 + j) {
                        case 0:
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 1); //easy
                            level->start();
                            // Handle Level 1 button click
                            // toLevelMenu("Level 1", 1);
                            break;
                        case 1:
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 2); //easy
                            level->start();
                            // Handle Level 2 button click
                            // toLevelMenu("Level 1", 2);
                            break;
                            // Repeat for the rest of the cases
                        case 2:
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 3); //easy
                            level->start();
                            // Handle Level 3 button click
                            // toLevelMenu("Level 1", 3);
                            break;
                        case 3:
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 1); //medium
                            level->start();
                            // Handle Level 4 button click
                            // toLevelMenu("Level 2", 1);
                            break;
                        case 4:
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 2); //medium
                            level->start();
                            // Handle Level 5 button click
                            // toLevelMenu("Level 2", 2);
                            break;
                        case 5:
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 3); //medium
                            level->start();
                            // Handle Level 6 button click
                            // toLevelMenu("Level 2", 3);
                            break;
                        case 6:
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 1); //hard
                            level->start();
                            // Handle Level 7 button click
                            // toLevelMenu("Level 3", 1);
                            break;
                        case 7:
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 2); //hard
                            level->start();
                            // Handle Level 8 button click
                            // toLevelMenu("Level 3", 2);
                            break;
                        case 8:
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 3); //hard
                            level->start();
                            // Handle Level 9 button click
                            // toLevelMenu("Level 3", 3);
                            break;
                        default:
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 1); //so i can delete the pionter down there
                            break;
                        }
                        delete level;
                        level = nullptr;
                    }
                }
            }
        }
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw background image
        DrawTexturePro(background, { 0.0f, 0.0f, (float)background.width, (float)background.height },
            { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() }, { 0.0f, 0.0f }, 0.0f, WHITE);

        // Draw logo centered horizontally and vertically
        DrawTexture(logo, (GetScreenWidth() - logo.width) / 2, 70, WHITE);

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

    // Calculate text position to align to the center of the screen
    Vector2 textPosition;
    textPosition.x = (GetScreenWidth() - MeasureTextEx(customFont, howToPlayText.c_str(), 24, 0).x) / 2;
    textPosition.y = 300;

    // Calculate arrow button position and size based on screen dimensions
    const float screenWidth = GetScreenWidth();
    const float screenHeight = GetScreenHeight();
    const float arrowButtonWidth = screenWidth * 0.1f;
    const float arrowButtonHeight = screenHeight * 0.1f;
    const float arrowButtonX = screenWidth * 0.05f;
    const float arrowButtonY = screenHeight * 0.8f;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            // Go back to main menu
            return;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Check if the arrow button is clicked
            if (CheckCollisionPointRec(GetMousePosition(), { arrowButtonX, arrowButtonY, arrowButtonWidth, arrowButtonHeight })) {
                // Go back to main menu
                return;
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw background image
        DrawTexture(background, 0, 0, WHITE);

        // Draw How to Play text aligned to the center
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
        "OMAR ELHAKIM \n\n"
        "AHMED ESSAM \n\n"
        "OMAR TEBRY \n\n"
        "OSAMA MAHMOUD \n\n"
        "OMAR WATANY \n\n"
        "AHMED ALI ";

    // Calculate text position to center it on the screen
    Vector2 textPosition;
    textPosition.x = (GetScreenWidth() - MeasureTextEx(customFont, creditsText.c_str(), 32, 0).x) / 2;
    textPosition.y = (GetScreenHeight() - MeasureTextEx(customFont, creditsText.c_str(), 32, 0).y) / 2;

    // Calculate arrow button position and size based on screen dimensions
    const float screenWidth = GetScreenWidth();
    const float screenHeight = GetScreenHeight();
    const float arrowButtonWidth = screenWidth * 0.1f;
    const float arrowButtonHeight = screenHeight * 0.1f;
    const float arrowButtonX = screenWidth * 0.05f;
    const float arrowButtonY = screenHeight * 0.8f;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            // Go back to main menu
            return;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Check if the arrow button is clicked
            if (CheckCollisionPointRec(GetMousePosition(), { arrowButtonX, arrowButtonY, arrowButtonWidth, arrowButtonHeight })) {
                // Go back to main menu
                return;
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw background image
        DrawTexture(background, 0, 0, WHITE);

        // Draw credits text aligned to the center
        DrawTextEx(customFont, creditsText.c_str(), textPosition, 32, 0, buttonColor);

        // Draw arrow button
        DrawTexture(arrowTexture, arrowButtonX, arrowButtonY, WHITE);

        EndDrawing();
    }
}
