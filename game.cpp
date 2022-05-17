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
float calculate_angle(Vector2 navaPosition)
{
    //get mouse coordinates
    Vector2 mousePosition = GetMousePosition();
    //calculate angle
    float angle = (float)atan2(mousePosition.y - navaPosition.y, mousePosition.x - navaPosition.x);
    //draw angle
    DrawText(TextFormat("%f",angle*(180.0/3.141592653589793238463)), 100, 10, 20, RED);
    return angle*(180.0/3.141592653589793238463);

}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] game - gravitas");
    Texture2D planet = LoadTexture("../assets/planets.png");
    Texture2D spaceship = LoadTexture("../assets/spaceship.png");
    //draw a black background
    int_bg();
    SetTargetFPS(144);
    float framewidth = planet.width / 50;
    float frameheight = planet.height / 4;
    float framewidth_space = spaceship.width / 18;
    float frameheight_space = spaceship.height / 10;
    float timer = 0.0f;
    int frame = 0;
    int frame2 = 0;
    int max_frames_w = planet.width / framewidth;
    int max_frames_h = planet.height / frameheight;
    Vector2 navaPosition = { (float)0, (float)0 };
    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawText(TextFormat("Mouse: %.1f, %.1f", GetMousePosition().x, GetMousePosition().y), 400, 10, 20, RED);
        DrawText(TextFormat("Screen Size: %i, %i", SCREEN_WIDTH, SCREEN_HEIGHT), 400, 30, 20, RED);

        if (IsKeyDown(KEY_D)) navaPosition.x += 2.0f;
        if (IsKeyDown(KEY_A)) navaPosition.x -= 2.0f;
        if (IsKeyDown(KEY_W)) navaPosition.y -= 2.0f;
        if (IsKeyDown(KEY_S)) navaPosition.y += 2.0f;


            ClearBackground(RAYBLACK);
            timer+=GetFrameTime();
            if(timer>=0.02f)
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
         //   std::cout<<frame<<" "<<frame2<<std::endl;
           // DrawCircleV(Vector2{30,30},5,RED);
           draw_bg();
           // DrawLine(500, 900, GetMousePosition().x,GetMousePosition().y, RED);
           DrawFPS(10, 10);
           float degrees = calculate_angle(navaPosition);
           DrawTexturePro(planet, Rectangle{framewidth*frame,frameheight*frame2,framewidth,frameheight}, Rectangle{SCREEN_WIDTH/3,SCREEN_HEIGHT/3,framewidth*3,frameheight*3}, Vector2{0.5,0.5},0, WHITE);
           DrawTextureTiled(spaceship, Rectangle{framewidth_space*5,0,framewidth_space,frameheight_space}, Rectangle{navaPosition.x,navaPosition.y,framewidth_space,frameheight_space}, Vector2{0,0},degrees-90,1,WHITE);
            // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            //draw the spaceship at the angle calculated above
            
        EndDrawing();
    }

    CloseWindow();

    return 0;
}