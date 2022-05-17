#include "raylib.h"
#include <random>
#include <cstdlib>
#define RAYBLACK CLITERAL(Color){ 0, 0, 0, 0 }
int a[10][10];
std::vector<int> v;
void int_bg()
{
    //store random vaues in a vector
    for (int i = 0; i < 1000; i++)
    {
           v.push_back(rand() % 100);
    }
  
}
void draw_bg()
{
    
    for(int i=1;i<=1000;i++)
    {
            DrawCircleV(Vector2{(float)(v[i]*10),(float)(v[i+1]*10)},2,WHITE);
    }
}
int main(void)
{
    InitWindow(1000, 1000, "raylib [core] game - gravitas");
    //draw a black background
    int_bg();
    SetTargetFPS(144);
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYBLACK);
           // DrawCircleV(Vector2{30,30},5,RED);
           draw_bg();
           DrawFPS(10, 10);
           
            // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}