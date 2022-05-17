#include "raylib.h"
#include <iostream>
using namespace std;
#define blk Color{ 10, 10, 10, 255 }

int main(){

    //Init Code
    float fps_calc;
    const int screen_width=512;
    const int screen_height=512;
    const int speed=5;
    float moved_distance;
    float position=0;
    SetTargetFPS(10);
    InitWindow(screen_width, screen_height, "raylib");
    float final_speed;//calculated delta speed
    float delta_time; 
    //End Init
    Vector2 poz {200,200};
    Vector2 size {20,20};
    float sec=0;
    while (!WindowShouldClose())
    {   
        
        BeginDrawing();
        
                ClearBackground(blk);
                DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);
                DrawText("This is a test", 10, 100, 20, DARKGRAY);
                DrawFPS(10, 10);
                DrawRectangle((int)position,256,10,10,RED);

        EndDrawing();
        // fps=GetFPS();
        fps_calc=1000000/30;
        delta_time=GetFrameTime();
        final_speed = (speed * (delta_time / fps_calc))*1000000;
        cout<<delta_time<<" "<<final_speed<<" "<<endl;
        sec=sec+delta_time;
        // if(sec>=0.15)
        // {
        //     position+=7;
        //     sec=0;
        // }
        cout<<sec<<endl;
        position=position+final_speed;
        cout<<position<<endl;
        
    }   
    CloseWindow();
}