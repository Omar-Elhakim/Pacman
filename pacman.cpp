#include "pacman.h"
#include "raylib.h"
#include <iostream>
using namespace std;
    
pacman::pacman() {
    Image pac = LoadImage("assets/pac.png");
    ImageResize(&pac, 80, 150);
    InitWindow(800, 450, "raylib [core] example - basic window");
    Texture2D pacman1 = LoadTextureFromImage(pac);
    Rectangle box{ 0,0,floor(pac.width / 2.f),floor(pac.height / 4.f) };
    Vector2 position{ 150,150 };
    Vector2 direction = { 0, 0 };
    float speed = 0.05f;
    float x = 0;
    int a = 0;
    //funco(pacman1, position, direction, box, pac, speed, x, a);
    while (!WindowShouldClose())
    {
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("ana zhe2t <3", 150, 200, 50, DARKBLUE);
        DrawTextureRec(pacman1, box, position, WHITE);


        if (IsKeyDown(KEY_RIGHT)) {
            direction = { 0, 0 };
            box.height = pac.height / 4.f;
            box.y = 0 * box.width;
            a++;
            if (a % 5 == 0) {
                x++;
            }
            if (x > 2)x = 0;
            box.x = x * box.width;
            direction.x += speed;

        }
        if (direction.x > 0) {
            box.height = pac.height / 4.f;
            box.y = 0 * box.width;
            a++;
            if (a % 250 == 0) {
                x++;
            }
            if (x > 2)x = 0;
            box.x = x * box.width;
        }





        if (IsKeyDown(KEY_LEFT)) {
            direction = { 0, 0 };
            box.height = pac.height / 4.f;
            box.y = 1 * box.width;
            a++;
            if (a % 250 == 0) {
                x++;
            }
            if (x > 2)x = 0;
            box.x = x * box.width;
            direction.x -= speed;
        }
        if (direction.x < 0) {
            box.height = pac.height / 4.f;
            box.y = 1 * box.width;
            a++;
            if (a % 250 == 0) {
                x++;
            }
            if (x > 2)x = 0;
            box.x = x * box.width;
        }






        if (IsKeyDown(KEY_UP)) {
            direction = { 0, 0 };
            box.height = pac.height / 4.f;
            box.y = 2 * box.width;
            a++;
            if (a % 250 == 0) {
                x++;
            }
            if (x > 2)x = 0;
            box.x = x * box.width;
            direction.y -= speed;
        }
        if (direction.y < 0) {
            box.height = pac.height / 4.f;
            box.y = 2 * box.width;
            a++;
            if (a % 250 == 0) {
                x++;
            }
            if (x > 2)x = 0;
            box.x = x * box.width;
        }





        if (IsKeyDown(KEY_DOWN)) {
            direction = { 0, 0 };
            box.height = pac.height / 5.f;
            box.y = 3 * box.width;
            a++;
            if (a % 250 == 0) {
                x++;
            }
            if (x > 2)x = 0;
            box.x = x * box.width;
            direction.y += speed;
        }
        if (direction.y > 0) {
            box.height = pac.height / 5.f;
            box.y = 3 * box.width;
            a++;
            if (a % 250 == 0) {
                x++;
            }
            if (x > 2)x = 0;
            box.x = x * box.width;
        }


        position.x += direction.x;
        position.y += direction.y;

        EndDrawing();
    }

    CloseWindow();
   
}


/*
  void pacman::funco(Texture2D pacman1, Vector2 position, Vector2 direction, Rectangle box, Image pac, float speed, float x, int a) {
      
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextureRec(pacman1, box, position, WHITE);
        if (IsKeyDown(KEY_RIGHT)) {
            pacman::moveright(position, direction, box, pac, speed,x,a);
        }
        if (IsKeyDown(KEY_LEFT)) {
            pacman::moveleft(position, direction, box, pac, speed, x, a);
        }
        if (IsKeyDown(KEY_UP)) {
            pacman::moveup(position, direction, box, pac, speed, x, a);
        }
        if (IsKeyDown(KEY_DOWN)) {
            pacman::movedown(position, direction, box, pac, speed, x, a);
        }
        EndDrawing();
    }

    CloseWindow();
}
  void pacman::moveright(Vector2 position, Vector2 direction, Rectangle box, Image pac, float speed, float x, int a) {
      direction = { 0, 0 };
      box.height = pac.height / 4.f;
      box.y = 0 * box.width;
      a++;
      if (a % 250 == 0) {
          x++;
      }
      if (x > 2)x = 0;
      box.x = x * box.width;
      direction.x += speed;

      if (direction.x > 0) {
          box.height = pac.height / 4.f;
          box.y = 0 * box.width;
          a++;
          if (a % 250 == 0) {
              x++;
          }
          if (x > 2)x = 0;
          box.x = x * box.width;
      }


      position.x += direction.x;
      position.y += direction.y;
  }


  void pacman::moveleft(Vector2 position, Vector2 direction, Rectangle box, Image pac, float speed, float x, int a) {
      direction = { 0, 0 };
      box.height = pac.height / 4.f;
      box.y = 1 * box.width;
      a++;
      if (a % 250 == 0) {
          x++;
      }
      if (x > 2)x = 0;
      box.x = x * box.width;
      direction.x -= speed;

      if (direction.x < 0) {
          box.height = pac.height / 4.f;
          box.y = 1 * box.width;
          a++;
          if (a % 250 == 0) {
              x++;
          }
          if (x > 2)x = 0;
          box.x = x * box.width;
      }
      position.x += direction.x;
      position.y += direction.y;
  }




  void pacman::moveup(Vector2 position, Vector2 direction, Rectangle box, Image pac, float speed, float x, int a) {
          direction = { 0, 0 };
          box.height = pac.height / 4.f;
          box.y = 2 * box.width;
          a++;
          if (a % 250 == 0) {
              x++;
          }
          if (x > 2)x = 0;
          box.x = x * box.width;
          direction.y += speed;
      if (direction.y > 0) {
          box.height = pac.height / 4.f;
          box.y = 2 * box.width;
          a++;
          if (a % 250 == 0) {
              x++;
          }
          if (x > 2)x = 0;
          box.x = x * box.width;
      }
      position.x += direction.x;
      position.y += direction.y;
  }



  void pacman::movedown(Vector2 position, Vector2 direction, Rectangle box, Image pac, float speed, float x, int a) {
      direction = { 0, 0 };
      box.height = pac.height / 5.f;
      box.y = 3 * box.width;
      a++;
      if (a % 250 == 0) {
          x++;
      }
      if (x > 2)x = 0;
      box.x = x * box.width;
      direction.y -= speed;

      if (direction.y < 0) {
          box.height = pac.height / 5.f;
          box.y = 3 * box.width;
          a++;
          if (a % 250 == 0) {
              x++;
          }
          if (x > 2)x = 0;
          box.x = x * box.width;
      }


      position.x += direction.x;
      position.y += direction.y;
  };
  */