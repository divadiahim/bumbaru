#include "raylib.h"
#include <random>
#include <cstdlib>
#include <iostream>
#define RAYBLACK CLITERAL(Color){ 0, 0, 0, 0 }
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
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
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] game - gravitas");
    Texture2D planet = LoadTexture("../assets/planets.png");
    //draw a black background
    int_bg();
    SetTargetFPS(144);
    float framewidth = planet.width / 50;
    float frameheight = planet.height / 4;
    float timer = 0.0f;
    int frame = 0;
    int frame2 = 0;
    int max_frames_w = planet.width / framewidth;
    int max_frames_h = planet.height / frameheight;
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYBLACK);
            timer+=GetFrameTime();
            if(timer>=0.05f)
            {
                frame++;
                if(frame>=max_frames_w)
                {
                    frame2++;
                }
                timer=0.0f;
            }
            frame = frame % max_frames_w;
            // if(frame2>=max_frames_h)
            // {
            //     frame2=0;
            // }
            frame2=frame2%max_frames_h;
            std::cout<<frame<<" "<<frame2<<std::endl;
           // DrawCircleV(Vector2{30,30},5,RED);
           draw_bg();
           DrawFPS(10, 10);
           DrawTexturePro(planet, Rectangle{framewidth*frame,frameheight*frame2,framewidth,frameheight}, Rectangle{SCREEN_WIDTH/3,SCREEN_HEIGHT/3,framewidth*3,frameheight*3}, Vector2{0.5,0.5},0, WHITE);
            // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}