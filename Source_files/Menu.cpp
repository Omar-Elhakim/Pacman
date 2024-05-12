#include "../Header_files/Menu.h"
#define RAYGUI_IMPLEMENTATION
#include "../raylib/include/raygui.h"
// Custom button structure




void mainMenu() {
    // Load background music
    Sound backgroundSound = LoadSound("assets/background_music.mp3");
    int s = 0;
    // Start playing the background music

    // Load common resources
    Texture2D background = LoadTexture("assets/background.png");
    Texture2D logo = LoadTexture("assets/logo.png");
    Font customFont = LoadFont("assets/Itim-Regular.ttf");

    // Custom button colors
    Color Yellow = { 249, 195, 40, 255 };
    Color Red = { 238, 35, 39, 255 };
    Color Cyan = { 127, 209, 218, 255 }; // B0EFF5
    Color textColor = BLACK; // Black color for text

    // Arrow button texture
    Texture2D arrowTexture = LoadTexture("assets/arrow.png");

    // Main menu variables
    const int NUM_OPTIONS = 5; // Number of buttons
    const char* menuOptions[NUM_OPTIONS] = { "START GAME", "HOW TO PLAY", "CREDITS", "QUIT GAME", "CREATE YOUR OWN MAP" }; // Menu options
    Rectangle buttons[NUM_OPTIONS]; // Button rectangles

    // Buttons positions and sizes
    const float buttonWidth = 246; // Width of each button rectangle
    const float buttonHeight = 60; // Height of each button rectangle
    const float buttonSpacing = 20; // Spacing between buttons
    const float startX = 277; // X-position for all buttons
    const float startY = 213; // Y-position for the first button

    // Set positions for each button
    buttons[0] = { startX, startY, buttonWidth, buttonHeight };
    buttons[1] = { startX, startY + buttonHeight + buttonSpacing + 10, buttonWidth, buttonHeight };
    buttons[2] = { startX, startY + (buttonHeight + buttonSpacing) * 2, buttonWidth, buttonHeight };
    buttons[3] = { startX, startY + (buttonHeight + buttonSpacing) * 2 + buttonHeight + 32, buttonWidth, buttonHeight };
    buttons[4] = { 627, 535, 138, 34 }; // Position the new button with its specific size

    // Custom button
    CustomButton button = {
        Rectangle{ 627, 535, 138, 34 },
        Cyan,
        "CREATE YOUR OWN MAP",
        10
    };

    // Variable to track the time of the last button press
    double lastButtonClickTime = 0.0;
    // Minimum time between button presses (in seconds)
    const double buttonCooldown = 0.5; // Adjust as needed

    // Main menu loop
    while (!WindowShouldClose()) {
        if (s % 8000 == 0) PlaySound(backgroundSound);
        s++;

        BeginDrawing();

        // Draw background image
        DrawTexture(background, 0, 0, WHITE);

        // Draw logo
        DrawTextureRec(logo, { 0, 0, 499, 213 }, { 151, 9 }, WHITE);

        // Set default button colors before the loop
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(textColor));
        GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(textColor));
        GuiSetStyle(BUTTON, TEXT_SIZE, 60);
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(Yellow));
        GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(Red));
        GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(textColor));
        GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, ColorToInt(textColor));
        GuiSetFont(customFont);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 30);

        for (int i = 0; i < NUM_OPTIONS; ++i) {
            if (i == NUM_OPTIONS - 1) {
                // Check collision only for the last button
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (CheckCollisionPointRec(GetMousePosition(), buttons[NUM_OPTIONS - 1]) &&
                        (GetTime() - lastButtonClickTime >= buttonCooldown)) {
                        // Call createMap function when the last button is clicked and debounce button click
                        createMap(background, logo, customFont, arrowTexture, backgroundSound);
                        lastButtonClickTime = GetTime(); // Update last button click time
                    }
                }

                // Draw the last button with custom font size
                DrawCustomButton(button);
            }
            else if (GuiButton(buttons[i], menuOptions[i])) {
                // Debounce button click for other buttons
                if (GetTime() - lastButtonClickTime >= buttonCooldown) {
                    switch (i) {
                    case 0: // Start Game button
                        toStartMenu(background, logo, customFont, arrowTexture, backgroundSound);
                        break;
                    case 1: // How to play button
                        toHowToPlay(background, logo, customFont, arrowTexture);
                        break;
                    case 2: // Credits button
                        toCredits(background, logo, customFont, arrowTexture);
                        break;
                    case 3: // Quit Game button
                        return;
                    }
                    lastButtonClickTime = GetTime(); // Update last button click time
                }
            }
        }

        EndDrawing();
    }

    // Unload common resources
    UnloadFont(customFont);
    UnloadTexture(logo);
    UnloadTexture(background);
    UnloadTexture(arrowTexture);

    // Stop and unload the background music
    StopSound(backgroundSound);
    UnloadSound(backgroundSound);
}


void toStartMenu(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture,Sound backgroundSound) {
    GuiSetStyle(DEFAULT, TEXT_SIZE, 17);
    // Custom button color (F9C328)
    Color Yellow = { 249, 195, 40, 255 };
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

        // Draw logo
        DrawTextureRec(logo, { 0, 0, 499, 213 }, { 151, 9 }, WHITE);

        // Draw difficulty text
        for (int i = 0; i < NUM_LEVELS; ++i) {
            DrawTextEx(customFont, difficultyNames[i], difficultyTextPos[i], 36, 0, textColor);
        }

        // Draw level buttons and text
        for (int i = 0; i < NUM_LEVELS; ++i) {
            for (int j = 0; j < 3; ++j) {
                Rectangle buttonRect = levelButtons[i][j];
                if (GuiButton(buttonRect, levelNames[j])) {
                    StopSound(backgroundSound);
                    // Handle button clicks for each level
                    Level* level;
                    bool f = 1;
                    int o;
                    switch (i * 3 + j) {
                    case 0:
                        while (f) {
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 1); //easy
                            if (level->start()) {
                                o=WinScreen(background, customFont);
                                if (o==1) {
                                    f = 1; break;
                                }//implement next level
                                else if (o==2)
                                {
                                    continue; //implement try again
                                }
                                else return; //to main menu
                            }
                            else {
                                if (LoseScreen(background, customFont)) continue; //implement try again
                                else return;//to main menu
                            }
                            delete level;
                            level = nullptr;
                        }
                        if (!f) break;
                        // Handle Level 1 button click
                        // toLevelMenu("Level 1", 1);
                    case 1:
                        while (f) {
                        level = new Level(GetScreenWidth(), GetScreenHeight(), 2); //easy
                        if (level->start()) {
                            o = WinScreen(background, customFont);
                            if (o == 1) {
                                f = 1; break;
                            }//implement next level
                            else if (o == 2)
                            {
                                continue; //implement try again
                            }
                            else return; //to main menu
                        }
                        else {
                            if (LoseScreen(background, customFont)) continue;
                            else return;
                        }
                        delete level;
                        level = nullptr;
                        }
                          if (!f) break;
                          // Repeat for the rest of the cases
                    case 2:
                        while (f) {
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 3); //easy
                            if (level->start()) {
                                o = WinScreen(background, customFont);
                                if (o == 1) {
                                    f = 1; break;
                                }//implement next level
                                else if (o == 2)
                                {
                                    continue; //implement try again
                                }
                                else return; //to main menu
                            }
                            else {
                                if (LoseScreen(background, customFont)) continue;
                                else return;
                            }
                        }
                        if (!f) break;

                    case 3:
                        while (f) {
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 1); //easy
                            if (level->start()) {
                                o = WinScreen(background, customFont);
                                if (o == 1) {
                                    f = 1; break;
                                }//implement next level
                                else if (o == 2)
                                {
                                    continue; //implement try again
                                }
                                else return; //to main menu
                            }
                            else {
                                if (LoseScreen(background, customFont)) continue;
                                else return;
                            }
                            delete level;
                            level = nullptr;
                        }
                        if (!f) break;
                    case 4:
                        while (f) {
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 2); //easy
                            if (level->start()) {
                                o = WinScreen(background, customFont);
                                if (o == 1) {
                                    f = 1; break;
                                }//implement next level
                                else if (o == 2)
                                {
                                    continue; //implement try again
                                }
                                else return; //to main menu
                            }
                            else {
                                if (LoseScreen(background, customFont)) continue;
                                else return;
                            }
                            delete level;
                            level = nullptr;
                        }
                        if (!f) break;
                    case 5:
                        while (f) {
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 3); //easy
                            if (level->start()) {
                                o = WinScreen(background, customFont);
                                if (o == 1) {
                                    f = 1; break;
                                }//implement next level
                                else if (o == 2)
                                {
                                    continue; //implement try again
                                }
                                else return; //to main menu
                            }
                            else {
                                if (LoseScreen(background, customFont)) continue;
                                else return;
                            }
                            delete level;
                            level = nullptr;
                        }
                        if (!f) break;
                    case 6:
                        while (f) {
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 1); //easy
                            if (level->start()) {
                                o = WinScreen(background, customFont);
                                if (o == 1) {
                                    f = 1; break;
                                }//implement next level
                                else if (o == 2)
                                {
                                    continue; //implement try again
                                }
                                else return; //to main menu
                            }
                            else {
                                if (LoseScreen(background, customFont)) continue;
                                else return;
                            }
                            delete level;
                            level = nullptr;
                        }
                        if (!f) break;
                    case 7:
                        while (f) {
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 2); //easy
                            if (level->start()) {
                                o = WinScreen(background, customFont);
                                if (o == 1) {
                                    f = 1; break;
                                }//implement next level
                                else if (o == 2)
                                {
                                    continue; //implement try again
                                }
                                else return; //to main menu
                            }
                            else {
                                if (LoseScreen(background, customFont)) continue;
                                else return;
                            }
                            delete level;
                            level = nullptr;
                        }
                        if (!f) break;
                    case 8:
                        while (f) {
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 3); //easy
                            if (level->start()) {
                                o = WinScreen(background, customFont);
                                if (o == 1) {
                                    f = 1; break;
                                }//implement next level
                                else if (o == 2)
                                {
                                    continue; //implement try again
                                }
                                else return; //to main menu
                            }
                            else {
                                if (LoseScreen(background, customFont)) continue;
                                else return;
                            }
                            delete level;
                            level = nullptr;
                        }
                        if (!f) break;
                    }
                    PlaySound(backgroundSound);
                }
            }
        }

        // Draw arrow button
        DrawTexture(arrowTexture, arrowButtonX, arrowButtonY, WHITE);

        EndDrawing();
    }
}

void toHowToPlay(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture) {
    // Custom button color (F9C328)
    Color Yellow = { 249, 195, 40, 255 };

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

        // Draw How to Play text
        DrawTextEx(customFont, howToPlayText.c_str(), textPosition, 24, 0, Yellow);

        // Draw arrow button
        DrawTexture(arrowTexture, arrowButtonX, arrowButtonY, WHITE);

        EndDrawing();
    }
}

void toCredits(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture) {
    // Custom button color (F9C328)
    Color Yellow = { 249, 195, 40, 255 };

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
    textPosition.x = (GetScreenWidth() - MeasureTextEx(customFont, creditsText.c_str(), 24, 0).x) / 2;
    textPosition.y = (GetScreenHeight() - MeasureTextEx(customFont, creditsText.c_str(), 24, 0).y) / 2;

    // Arrow button position and size
    const float arrowButtonWidth = 64;
    const float arrowButtonHeight = 64;
    const float arrowButtonX = 55;
    const float arrowButtonY = 504;

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

        // Draw credits text
        DrawTextEx(customFont, creditsText.c_str(), textPosition, 32, 0, Yellow);

        // Draw arrow button
        DrawTexture(arrowTexture, arrowButtonX, arrowButtonY, WHITE);

        EndDrawing();
    }
}

void createMap(Texture2D background, Texture2D logo, Font customFont, Texture2D arrowTexture, Sound backgroundSound)
{
    // Custom button colors
    Color Yellow = { 249, 195, 40, 255 };
    Color Red = { 238, 35, 39, 255 };
    Color Cyan = { 127, 209, 218, 255 }; // B0EFF5
    Color textColor = BLACK; // Black color for text

    // Main menu variables
    const int NUM_OPTIONS = 3;
    const char* menuOptions[NUM_OPTIONS] = { "EASY", "MEDIUM", "HARD" };
    Rectangle buttons[NUM_OPTIONS]; // Button rectangles

    // Buttons positions and sizes
    const float buttonWidth = 246; // Width of each button rectangle
    const float buttonHeight = 60; // Height of each button rectangle
    const float buttonSpacing = 20; // Spacing between buttons
    const float startX = 277; // X-position for all buttons
    const float startY = 213; // Y-position for the first button

    // Set positions for each button
    buttons[0] = { startX, startY, buttonWidth, buttonHeight };
    buttons[1] = { startX, startY + buttonHeight + buttonSpacing, buttonWidth, buttonHeight };
    buttons[2] = { startX, startY + (buttonHeight + buttonSpacing) * 2, buttonWidth, buttonHeight };

    // Arrow button position and size
    const float arrowButtonWidth = 64;
    const float arrowButtonHeight = 64;
    const float arrowButtonX = 55;
    const float arrowButtonY = 504;
    
    while (!WindowShouldClose())
    {

        if (IsKeyPressed(KEY_ESCAPE))
        {
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
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            // Check for clicks on Menu buttons
            for (int i = 0; i < NUM_OPTIONS; ++i)
            {
                if (CheckCollisionPointRec(GetMousePosition(), buttons[i]))
                {
                    Level* level;
                    bool f=1;
                    int o;
                    StopSound(backgroundSound);

                    switch (i)
                    {
                    case 0:
                        while (f) {
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 4); //easy
                            if (level->start()) {
                                o = WinScreen(background, customFont);
                                if (o == 1) {
                                    f = 1; break;
                                }//implement next level
                                else if (o == 2)
                                {
                                    continue; //implement try again
                                }
                                else f = 0; //to main menu
                            }
                            else {
                                if (LoseScreen(background, customFont)) continue; //implement try again
                                else f = 0;//to main menu
                            }
                            delete level;
                            level = nullptr;
                        }
                        if (!f) break;
                        // Handle Level 1 button click
                        // toLevelMenu("Level 1", 1);
                    case 1:
                        while (f) {
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 4); //easy
                            if (level->start()) {
                                o = WinScreen(background, customFont);
                                if (o == 1) {
                                    f = 1; break;
                                }//implement next level
                                else if (o == 2)
                                {
                                    continue; //implement try again
                                }
                                else f = 0; //to main menu
                            }
                            else {
                                if (LoseScreen(background, customFont)) continue;
                                else f = 0;
                            }
                            delete level;
                            level = nullptr;
                        }
                        if (!f) break;
                        // Repeat for the rest of the cases
                    case 2:
                        while (f) {
                            level = new Level(GetScreenWidth(), GetScreenHeight(), 4); //easy
                            if (level->start()) {
                                o = WinScreen(background, customFont);
                                if (o == 1) {
                                    f = 1; break;
                                }//implement next level
                                else if (o == 2)
                                {
                                    continue; //implement try again
                                }
                                else f = 0; //to main menu
                            }
                            else {
                                if (LoseScreen(background, customFont)) continue;
                                else f = 0;
                            }
                        }
                        if (!f) break;
                    }
                    PlaySound(backgroundSound);

//                    delete level;
  //                  level = nullptr;

                }
            }
        }
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw background image
        DrawTexture(background, 0, 0, WHITE);

        // Draw logo
        DrawTextEx(customFont, "CHOOSE THE DIFFICULTY", { (GetScreenWidth() - MeasureTextEx(customFont, "CHOOSE THE DIFFICULTY", 52, 2).x) / 2, 109 }, 52, 2, YELLOW);
        // DrawText("CHOOSE THE DIFFICULTY", 120,109,48,Yellow);
       // DrawTextureRec(logo, { 0, 0, 499, 213 }, { 151, 9 }, WHITE);

        // Set default button colors before the loop
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(textColor));
        GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(textColor));
        GuiSetStyle(BUTTON, TEXT_SIZE, 60);
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(Yellow));
        GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(Red));
        GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(textColor));
        GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, ColorToInt(textColor));
        GuiSetFont(customFont);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 30);

        for (int i = 0; i < NUM_OPTIONS; ++i)
        {

            // Draw other buttons with default font size
            GuiButton(buttons[i], menuOptions[i]);

        }

        // Draw arrow button
        DrawTexture(arrowTexture, arrowButtonX, arrowButtonY, WHITE);
        EndDrawing();
    }
}
    
// win/lose screens
int WinScreen(Texture2D background, Font customFont)
{
    // Custom button colors
    Color Yellow = { 249, 195, 40, 255 };
    Color Red = { 238, 35, 39, 255 };
    Color Cyan = { 127, 209, 218, 255 }; // B0EFF5
    Color textColor = BLACK; // Black color for text

    // Main menu variables
    const int NUM_OPTIONS = 3;
    const char* menuOptions[NUM_OPTIONS] = { "NEXT LEVEL", "TRY AGAIN","MAIN MENU" };
    Rectangle buttons[NUM_OPTIONS]; // Button rectangles

    // Buttons positions and sizes
    const float buttonWidth = 246; // Width of each button rectangle
    const float buttonHeight = 60; // Height of each button rectangle
    const float buttonSpacing = 36; // Spacing between buttons
    const float startX = 277; // X-position for all buttons
    const float startY = 213; // Y-position for the first button

    // Set positions for each button
    buttons[0] = { startX, startY, buttonWidth, buttonHeight };
    buttons[1] = { startX, startY + buttonHeight + buttonSpacing, buttonWidth, buttonHeight };
    buttons[2] = { startX, startY + (buttonHeight + buttonSpacing) * 2, buttonWidth, buttonHeight };

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ESCAPE))
        {
            // Go back to main menu
            return 0;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw background image
        DrawTexture(background, 0, 0, WHITE);

        // Draw "YOU WON !!" text
        DrawTextEx(customFont, "YOU WON !!", { (GetScreenWidth() - MeasureTextEx(customFont, "YOU WON !!", 60, 2).x) / 2, 109 }, 60, 2, YELLOW);
        // Draw "Your Score" text
        DrawTextEx(customFont, TextFormat("YOUR SCORE: %d", 5), { 54, 182 }, 20, 2, Red);

        // Draw "Highest Scores" text
        DrawTextEx(customFont, "HIGHEST SCORE:", { 617, 182 }, 20, 2, Red);
        vector<int>highestScores = readScore();
        // Draw individual highest scores
        for (size_t i = 0; i < 3; ++i) {
            DrawTextEx(customFont, TextFormat("%d - %d", i + 1, highestScores[i]), { 617, 182 + static_cast<float>(i + 1) * 35 }, 20, 2, Red);
        }


        // Set default button colors before the loop
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(textColor));
        GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(textColor));
        GuiSetStyle(BUTTON, TEXT_SIZE, 60);
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(Yellow));
        GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(Red));
        GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(textColor));
        GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, ColorToInt(textColor));
        GuiSetFont(customFont);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 30);

        for (int i = 0; i < NUM_OPTIONS; ++i)
        {
            // Draw buttons
            if (GuiButton(buttons[i], menuOptions[i]))
            {
                // If button clicked, return appropriate value
                switch (i)
                {
                case 0: // Next Level button
                    return 1;
                case 1: // Try Again button
                    return 2;
                case 2: // Main Menu button
                    return 0;
                default:
                    break;
                }
            }
        }

        EndDrawing();
    }

    // Return 0 by default (if window closes without button click)
    return 0;
}

bool LoseScreen(Texture2D background, Font customFont)
{
    // Custom button colors
    Color Yellow = { 249, 195, 40, 255 };
    Color Red = { 238, 35, 39, 255 };
    Color textColor = BLACK; // Black color for text

    // Lose menu variables
    const int NUM_OPTIONS = 2;
    const char* menuOptions[NUM_OPTIONS] = { "TRY AGAIN", "MAIN MENU" };
    Rectangle buttons[NUM_OPTIONS]; // Button rectangles

    // Buttons positions and sizes
    const float buttonWidth = 246; // Width of each button rectangle
    const float buttonHeight = 60; // Height of each button rectangle
    const float buttonSpacing = 36; // Spacing between buttons
    const float startX = 277; // X-position for all buttons
    const float startY = 286; // Y-position for the first button (adjusted for lose screen)

    // Set positions for each button
    buttons[0] = { startX, startY, buttonWidth, buttonHeight };
    buttons[1] = { startX, startY + buttonHeight + buttonSpacing, buttonWidth, buttonHeight };

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ESCAPE))
        {
            // Go back to main menu
            return false;
        }
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw background image
        DrawTexture(background, 0, 0, WHITE);

        // Draw "YOU LOST !!" text
        DrawTextEx(customFont, "YOU LOST !!", { (GetScreenWidth() - MeasureTextEx(customFont, "YOU LOST !!", 60, 2).x) / 2, 109 }, 60, 2, Yellow);
        // Draw "Your Score" text
        DrawTextEx(customFont, TextFormat("YOUR SCORE: %d", 5), { 54, 182 }, 30, 2, Red);

        // Set default button colors before the loop
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(textColor));
        GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(textColor));
        GuiSetStyle(BUTTON, TEXT_SIZE, 60);
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(Yellow));
        GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(Red));
        GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(textColor));
        GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, ColorToInt(textColor));
        GuiSetFont(customFont);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 30);

        for (int i = 0; i < NUM_OPTIONS; ++i)
        {
            // Draw buttons
            if (GuiButton(buttons[i], menuOptions[i]))
            {
                // If button clicked, return appropriate value
                switch (i)
                {
                case 0: // Try Again button
                    return true;
                case 1: // Main Menu button
                    return false;
                default:
                    break;
                }
            }
        }

        EndDrawing();
    }

    // Return false by default (if window closes without button click)
    return false;
}



// Custom drawing function for the last button with specific font size
    void DrawCustomButton(CustomButton button) 
    {

        Font customFont = LoadFont("assets/Itim-Regular.ttf");

        // Draw button background
        DrawRectangleRec(button.bounds, button.color);

        // Draw button border
        DrawRectangleLinesEx(button.bounds, 2, BLACK);

        // Calculate text width and height
        float textWidth = MeasureText(button.text, button.fontSize);
        float textHeight = button.fontSize;

        // Calculate text position to center it within the button
        float textX = button.bounds.x + (button.bounds.width - textWidth) / 2;
        float textY = button.bounds.y + (button.bounds.height - textHeight) / 2;

        // Draw button text
        DrawTextEx(
            customFont, // Font to use for drawing
            button.text, // Text string to draw
            Vector2{ textX, textY }, // Position to draw the text
            button.fontSize, // Font size
            2, // Spacing between characters
            BLACK // Text color
        );
    }