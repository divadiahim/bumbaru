
#include "include/raylib.h"
#define PHYSAC_IMPLEMENTATION
#include "include/physac.h"
#include <vector>
#define Width 1000
#define Height 1000
#define limit Height - 200
#define G 400
#define PLAYER_JUMP_SPD 350.0f
#define PLAYER_HOR_SPD 200.0f

const int screenWidth = 1000;
const int screenHeight = 1000;
bool canJump = 0;
int mihaiGame = 0;

void UpdatePlayer(PhysicsBody player, PhysicsBody platforms, int envItemsLength, float delta);

void UpdateCameraCenter(Camera2D *camera, PhysicsBody *player, PhysicsBody platforms, int envItemsLength, float delta, int Screenwidth, int Screenheight);

Vector2 platformPos = Vector2{Width / 2.0f, (float)limit};
PhysicsBody platforms[] = {
    CreatePhysicsBodyRectangle(Vector2{500, 950}, 500, 100, 10), /// base
    CreatePhysicsBodyRectangle(Vector2{0, 750}, 800, 20, 10),    /// 1
    CreatePhysicsBodyRectangle(Vector2{700, 500}, 400, 20, 10),  /// 2
    CreatePhysicsBodyRectangle(Vector2{250, 500}, 300, 20, 10),  /// 3
    CreatePhysicsBodyRectangle(Vector2{750, 250}, 700, 20, 10),  /// 4
    /*CreatePhysicsBodyRectangle(Vector2{}, 400, 60 );///5
    CreatePhysicsBodyRectangle(Vector2{0,}, );///6
    CreatePhysicsBodyRectangle(Vector2{}, , , );
    CreatePhysicsBodyRectangle(Vector2{0,}, , , );*/
};
PhysicsBody player = CreatePhysicsBodyCircle(Vector2{500, 900}, 30, 10);

void DrawAllBodies()
{
    int bodiesCount = GetPhysicsBodiesCount();
    for (int i = 0; i < bodiesCount; i++)
    {
        PhysicsBody player = GetPhysicsBody(i);

        int vertexCount = GetPhysicsShapeVerticesCount(i);
        for (int j = 0; j < vertexCount; j++)
        {
            // Get physics bodies shape vertices to draw lines
            // Note: GetPhysicsShapeVertex() already calculates rotation transformations
            Vector2 vertexA = GetPhysicsShapeVertex(player, j);

            int jj = (((j + 1) < vertexCount) ? (j + 1) : 0); // Get next vertex or first to close the shape
            Vector2 vertexB = GetPhysicsShapeVertex(player, jj);

            DrawLineEx(vertexA, vertexB, 5, LIGHTGRAY); // Draw a line between two vertex positions
        }
    }
}
/// movement functions:
void Strafe()
{
    if (IsKeyDown(KEY_LEFT))
        player->velocity.x = -0.2;
    else if (IsKeyDown(KEY_RIGHT))
        player->velocity.x = 0.2;
}

void VerticalMove()
{
    if (IsKeyDown(KEY_UP))
        player->velocity.y = -1;
}

float offset1 = 0, offset2 = 0;
void MovePlatform()
{
    offset1 += PI / 100;
    if (offset1 == 10 * PI)
        offset1 = 0;
    for (int i = 1; i < 5; i++)
    {
        if (i % 2 == 0)
            platforms[i]->velocity.y = 0.15 * (float)sin(offset1); /// doar pt ce se misca <3
        else
            platforms[i]->velocity.y = -0.15 * (float)sin(offset1); /// doar pt ce se misca <3
    }
}
std::vector<int> v;
void int_bg()
{
    // store random vaues in a vector
    for (int i = 0; i < 1000; i++)
    {
        v.push_back(rand() % 100);
    }
}
void draw_bg()
{
    for (int i = 1; i <= 1000; i++)
    {
        DrawCircleV(Vector2{(float)(v[i] * 10), (float)(v[i + 1] * 10)}, 2, WHITE);
    }
}

void MovePlanet(){
    offset2 += PI / 100;
    if(offset2 == 10 * PI) offset2 = 0; 
}






// main loop:
int main(void)
{
    InitWindow(Width, Height, "");
    SetTargetFPS(120);
    InitPhysics();
    int_bg();
    player->freezeOrient = true;
    // arrive->freezeOrient = true;
    for (int i = 0; i < 5; i++)
    {
        platforms[i]->freezeOrient = true;
        platforms[i]->staticFriction = platforms[i]->dynamicFriction = 0;
        platforms[i]->useGravity = false;

    }
    platforms[0]->enabled = false;
    // arrive->enabled = false;
    Texture2D planets = LoadTexture("../assets/planets.png");
    bool EnterPressed = false; 
    Texture2D texture = LoadTexture("../assets/planetAnim.png");
    Rectangle frameRec = { 0.0f, 0.0f, (float)texture.width/50, (float)texture.height};
     int currentFrame = 0;
    int framesCounter = 0;
    while (!WindowShouldClose())
    {
        if(EnterPressed){
        draw_bg();
        for (int i = 0; i < 5; i++)
        {
            platforms[i]->velocity.x = 0;
        }
        UpdatePhysics();
        VerticalMove();
        Strafe();
        MovePlatform();
        BeginDrawing();
        ClearBackground(BLACK); 
        DrawTexturePro(planets, Rectangle{(float)(planets.width / 50), (float)(planets.height / 4), (float)(planets.width / 50), (float)(planets.height / 4)}, Rectangle{(float)(650), (float)(-550), (float)(planets.width / 50) * 7, (float)(planets.height / 4) * 7}, Vector2{500, 0}, 0, WHITE);
        if (CheckCollisionPointRec(player->position, Rectangle{150, 0, 700, 110}))
        {
            system("..\\build\\game.exe");
            CloseWindow();
        }
        DrawFPS(Width - 90, Height - 30);
        DrawAllBodies();
        DrawText("/|\\ to climb", 600, 700, 30, LIGHTGRAY);
        DrawText("-> to slide to the right", 600, 740, 30, LIGHTGRAY);
        DrawText("\\|/ to descend", 600, 780, 30, LIGHTGRAY);
        DrawText("<- to slide to the left", 600, 820, 30, LIGHTGRAY);
        EndDrawing();
        }
        else {
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
                DrawTextureRec(texture, frameRec, Vector2{30 , screenHeight/2 + 10 * (float)sin(offset2)} , WHITE);
            EndDrawing();
            if(IsKeyPressed(KEY_ENTER))EnterPressed = true;
        }
    }
    ClosePhysics();
    CloseWindow();
   
    return 0;
}