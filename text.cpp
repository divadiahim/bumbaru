#include "include/raylib.h"
#include <cstdlib>
#define PHYSAC_IMPLEMENTATION
#include "include/physac.h"
#define screenWidth 1000
#define screenHeight 1000
///variables:
int v[1000];
Color starColor[] = {WHITE, YELLOW}; 
float offset = 0;
void int_bg()
{
    //store random vaues in a vector
    for (int i = 0; i < 1000; i++)
    {
           v[i] = rand() % 100;
    }
   
}

void draw_bg()
{ 
    for(int i=0;i<1000;i++)
    {
        DrawCircleV(Vector2{(float)(v[i]*15),(float)(v[i+1]*15)}, 2, starColor[i%2]);
    }
}


void MovePlanet(){
    offset += PI / 100;
    if(offset == 10 * PI) offset = 0; 
}
 

int main(void)
{
   
    Texture2D texture = LoadTexture("assets/planetAnim.png");
    Rectangle frameRec = { 0.0f, 0.0f, (float)texture.width/50, (float)texture.height};
    int_bg();
    InitWindow(screenWidth, screenHeight, "Game");
    Texture2D texture = LoadTexture("assets/planetAnim.png");
    Rectangle frameRec = { 0.0f, 0.0f, (float)texture.width/50, (float)texture.height};
     int currentFrame = 0;
    int framesCounter = 0;
        while(!WindowShouldClose()){
            framesCounter++;
        if (framesCounter >= (10))
        {
            framesCounter = 0;
            currentFrame++;
            if (currentFrame > 49) currentFrame = 0;
            frameRec.x = (float)currentFrame*(float)texture.width/50;
        }
            MovePlanet();
            BeginDrawing();
                ClearBackground(BLACK);
                DrawText("GAME TITLE", screenWidth/2 - 90, screenHeight/2 - 100, 30, LIME);
                DrawText("Powered by zenCode", screenWidth - 120,  screenHeight - 15, 10, WHITE);
                DrawText("Press Enter to start the game!", screenWidth/2, 3 * screenHeight/4, 20, LIGHTGRAY);
                 draw_bg();
                DrawTextureRec(texture, frameRec, Vector2{30 , screenHeight/2 + 10 * (float)sin(offset)} , WHITE);
            EndDrawing();
        }
    UnloadTexture(texture);
    CloseWindow();       
    return 0;
}


