#include "raylib.h"
#include <iostream>
//#include "raymath.h"
#define PHYSAC_IMPLEMENTATION
#include "physac.h"
#define G 400
#define PLAYER_JUMP_SPD 350.0f
#define PLAYER_HOR_SPD 200.0f

typedef struct Player {
    Vector2 position;
    float speed;
    bool canJump;
} Player;
Rectangle playerRect;
typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;

void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta);

void UpdateCameraCenter(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [texture] example - image text drawing");

    Texture2D texture = LoadTexture("../assets/try.png");
    Image planet = LoadImage("../assets/white_texture.png");
    Texture2D planetTexture = LoadTextureFromImage(planet);
    Vector2 position = { (float)(screenWidth/2 - texture.width/2), (float)(screenHeight/2 - texture.height/2 - 20) };

    Player player = { 0 };
    player.position = (Vector2){ 400, 400 };
    player.speed = 0;
    player.canJump = false;
    EnvItem envItems[] = {///asta e structura
        ///{{ 0, 0, 1000, 400 }, 0, BLACK },
        {{ 0, 400, screenWidth, 400 }, 1, LIGHTGRAY },///baza
        {{ 0, 0, 0, 0 }, 1, LIGHTGRAY },///5 st
        {{ 75, -220, 600, 20 }, 1, LIGHTGRAY },///5 dr
        {{ -screenWidth, -100, 820, 20 }, 1, LIGHTGRAY }, ///4 st
        {{ 0, 0, 0, 0 }, 1, LIGHTGRAY },///4 dr
        {{ -30, 40, 700, 20 }, 1, LIGHTGRAY }, ///3 st
        {{ 0, 0, 0, 0 }, 1, LIGHTGRAY },///3 dr
        {{ 0, 0, 0, 0 }, 1, LIGHTGRAY }, ///2 st
        {{ 150, 170, screenWidth + (screenWidth - 150), 20 }, 1, LIGHTGRAY },///2 dr
        {{ -screenWidth, 290, 1350, 20 }, 1, LIGHTGRAY },///1 st
        {{ 0, 0, 0, 0 }, 1, LIGHTGRAY }///1 dr
    };
///{{ 650, 250, screenWidth + (screenWidth - 650), 20 }, 1, LIGHTGRAY }///1 dr
///{{ -screenWidth, 100, 850, 20 }, 1, LIGHTGRAY }, ///2 st
///{{ 500, -50, screenWidth + (screenWidth - 500), 20 }, 1, LIGHTGRAY },///3 dr
///{{ 120, -200, screenWidth + (screenWidth - 120), 20 }, 1, LIGHTGRAY },///4 dr
///{{ -screenWidth, -350, 1350, 20 }, 1, LIGHTGRAY },///5 st



    int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);

    Camera2D camera = { 0 };
    camera.target = player.position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Store pointers to the multiple update camera functions
    void (*cameraUpdaters[])(Camera2D*, Player*, EnvItem*, int, float, int, int) = {
        UpdateCameraCenter,
    };

    int cameraOption = 0;
    int cameraUpdatersLength = sizeof(cameraUpdaters)/sizeof(cameraUpdaters[0]);
    

    float timer = 0.0f;
    int frame = 0;
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        float deltaTime = GetFrameTime();

        UpdatePlayer(&player, envItems, envItemsLength, deltaTime);

        camera.zoom += ((float)GetMouseWheelMove()*0.05f);///trb comentat dupa

        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.25f) camera.zoom = 0.25f;

        if (IsKeyPressed(KEY_R))
        {
            camera.zoom = 1.0f;
            player.position = (Vector2){ 400, 400 };
        }

        if (IsKeyPressed(KEY_C)) cameraOption = (cameraOption + 1)%cameraUpdatersLength;

        // Call update camera function by its pointer
        cameraUpdaters[cameraOption](&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            /*DrawTexturePro(planet, Rectangle{framewidth*frame,frameheight*frame2,framewidth,frameheight}, 
Rectangle{SCREEN_WIDTH/3,SCREEN_HEIGHT/3,framewidth*3,frameheight*3}, Vector2{0.5,0.5},0, WHITE);*/
            //DrawTexture(texture, 0, 0, WHITE);
            //DrawTexturePro(planetTexture, Rectangle{2048,2048}, Rectangle{800,450}, Vector2{0,0}, 0, WHITE);
            
            timer += GetFrameTime();

            if(timer >= 0.2f){
                timer = 0.0f;
                frame +=1;
            }

            BeginMode2D(camera);

                DrawRectangleRec(envItems[0].rect, envItems[0].color);
                for (int i = 1; i < envItemsLength; i++) 
                    {
                        if((frame/5)%2==0)
                        {
                            if(i%2==1)///stanga
                                envItems[i].rect.y += (5 - (frame) % 5)*0.2;
                            else envItems[i].rect.y -= (5 - (frame) % 5)*0.2;///dreapta
                            ///CreatePhysicsBodyRectangle({envItems[i].rect.x, envItems[i].rect.y},envItems[i].rect.width, envItems[i].rect.height, 100);
                            DrawRectangleRec(envItems[i].rect, envItems[i].color);
                        }
                        else
                        {
                            if(i%2==1)///stanga
                                envItems[i].rect.y -= ((5 - (frame) % 5))*0.2;
                            else envItems[i].rect.y += ((5 - (frame) % 5))*0.2;///dreapta
                            ///CreatePhysicsBodyRectangle({envItems[i].rect.x, envItems[i].rect.y},envItems[i].rect.width, envItems[i].rect.height, 100);
                            DrawRectangleRec(envItems[i].rect, envItems[i].color);
                        }
                    }
                    /*if((frame/5)%2==0)
                        {
                            DrawRectangleRec(Rectangle{ 650 ,(float)250 + frame % 5, screenWidth + (screenWidth - 650), 20}, LIGHTGRAY);///1dr
                            DrawRectangleRec(Rectangle{ -screenWidth, (float)250 + (5 - (frame) % 5), 1350, 20}, LIGHTGRAY);///1st
                        }

                    else 
                        {   
                            DrawRectangleRec(Rectangle{ 650 , (float)250 + (5 - frame % 5), screenWidth + (screenWidth - 650), 20}, LIGHTGRAY);///1dr
                            DrawRectangleRec(Rectangle{ -screenWidth, (float)250 + (frame) % 5, 1350, 20}, LIGHTGRAY);///1st
                        }*/

                playerRect = { player.position.x - 20, player.position.y - 40, 40, 40 };
                DrawRectangleRec(playerRect, RED);

            EndMode2D();

            /*DrawText("Controls:", 20, 20, 10, BLACK);
            DrawText("- Right/Left to move", 40, 40, 10, DARKGRAY);
            DrawText("- Space to jump", 40, 60, 10, DARKGRAY);
            DrawText("- Mouse Wheel to Zoom in-out, R to reset zoom", 40, 80, 10, DARKGRAY);
            DrawText("Current camera mode:", 20, 120, 10, BLACK);
            DrawText(cameraDescriptions[cameraOption], 40, 140, 10, DARKGRAY);*/

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    UnloadTexture(texture);
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta)
{
    if (IsKeyDown(KEY_LEFT)) player->position.x -= PLAYER_HOR_SPD*delta;
    if (IsKeyDown(KEY_RIGHT)) player->position.x += PLAYER_HOR_SPD*delta;
    if (IsKeyDown(KEY_SPACE) && player->canJump)
    {
        player->speed = -PLAYER_JUMP_SPD;
        player->canJump = false;
    }

    int hitObstacle = 0;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        Vector2 *p = &(player->position);
        if (ei->blocking &&
            ei->rect.x <= p->x &&
            ei->rect.x + ei->rect.width >= p->x &&
            ei->rect.y >= p->y &&
            ei->rect.y < p->y + player->speed*delta)
        {
            hitObstacle = 1;
            player->speed = 0.0f;
            p->y = ei->rect.y;
        }
    }
        /*if(i!=0 && CheckCollisionPointRec(Vector2{p->x - 20, p->y - 40}, ei->rect))
        {
            hitObstacle = 1;
            player->speed = 0.0f;
            player->position = (Vector2){ 400, 400 };
        }*/
        /*if(CheckCollisionRecs(ei->rect, {p->x, p->y, 0, 0}))
        {
            hitObstacle = 1;
            player->speed = 0.0f;
            EnvItem *ei2 = envItems + i + 1;
            p->y = ei2->rect.y;
        }*/

    if (!hitObstacle)
    {
        player->position.y += player->speed*delta;
        player->speed += G*delta;
        player->canJump = false;
    }
    else player->canJump = true;
}
void UpdateCameraCenter(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
    camera->offset = (Vector2){ width/2.0f, height/2.0f };
    camera->target = player->position;
}