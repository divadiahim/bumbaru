
#include "raylib.h"
#include "include/raymath.h"
#include <random>
#include <cstdlib>
#include <iostream>
#define RAYBLACK \
    CLITERAL(Color) { 0, 0, 0, 0 }
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
int a[10][10];
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
float calculate_angle(Vector2 navaPosition)
{
    // get mouse coordinates
    Vector2 mousePosition = GetMousePosition();
    // calculate angle
    float angle = (float)atan2(mousePosition.y - navaPosition.y, mousePosition.x - navaPosition.x);
    // draw angle
    DrawText(TextFormat("%f", angle * (180.0 / 3.141592653589793238463)), 100, 10, 20, RED);
    return angle * (180.0 / 3.141592653589793238463);
}
typedef struct Shoot
{
    Vector2 start_poz;
    Vector2 end_poz;
    Vector2 speed;
    bool active;
    Color color;
} Shoot;

// max bullets
#define NUM_SHOOTS 50

// array of bullets to reuse
static Shoot shoot[NUM_SHOOTS];

// to reduce the shoot per second
static int shootRate;
struct bullet
{
    float len = 10;
    float offset = 1;
};
struct bullet bullets[100];
float o1 = 0.005;
float l1 = 15;
Rectangle rect1;

void bullet(Vector2 navaPosition,Vector2 mousePosition)
{
    static int offset = 1;

    // get mouse coordinates
    //Vector2 mousePosition = GetMousePosition();
    // int a = mousePosition.y - navaPosition.y;
    // int b = mousePosition.x - navaPosition.x;
    //  float angle = (float)atan2(mousePosition.y - navaPosition.y, mousePosition.x - navaPosition.x);
    // DrawText(TextFormat("%f %f",len*sin(angle),len*sin(angle)), 200, 100, 20, RED);
    // int len2=sqrt(a*a+b*b);
    // DrawLineEx(Vector2{(float)(navaPosition.x),(float)(navaPosition.y)},Vector2{(float)((len+len2)*cos(angle)),(float)((len+len2)*sin(angle))},10,RED);
    Vector2 start_pos = {navaPosition.x, navaPosition.y};
    Vector2 end_pos = {mousePosition.x, mousePosition.y};
    // Vector2 start_pos = {500,500};
    // Vector2 end_pos = {100,20};
    Vector2 poz_3 = Vector2Normalize(Vector2Subtract(end_pos, start_pos));

    // print len and offset
    DrawLineEx(start_pos, Vector2Add(start_pos, poz_3), 10, RED);
    for (int i = 0; i < 1; i++)
    {
        bullets[i].len += l1;
        std::cout << bullets[i].len << " " << bullets[i].offset << std::endl;
        // start_pos.x+=bullets[i].offset;
        // start_pos.y+=bullets[i].offset;
        poz_3.x *= bullets[i].len;
        poz_3.y *= bullets[i].len;
        Vector2Normalize(start_pos);
        // start_pos.x*=bullets[i].offset;
        // start_pos.y*=bullets[i].offset;
        //   DrawLineEx(start_pos,Vector2Add(start_pos,poz_3),10,RED);
        DrawCircleV(Vector2Add(start_pos, poz_3), 10, RED);
    }
}
bool prssed = 0;
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitAudioDevice();
    Sound fxWav = LoadSound("../assets/sf_laser_15.mp3");
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] game - gravitas");
    Texture2D planet = LoadTexture("../assets/planets.png");
    Texture2D spaceship = LoadTexture("../assets/spaceship.png");
    // draw a black background
    int_bg();
    SetTargetFPS(144);
    float framewidth = planet.width / 50;
    float frameheight = planet.height / 4;
    float framewidth_space = spaceship.width / 18;
    float frameheight_space = spaceship.height / 10;
    float timer = 0.0f;
    int frame = 0;
    int frame2 = 0;
    float timer2 = 0.0f;
    int frame3 = 0;
    Vector2 mousepoz;
    int max_frames_w = planet.width / framewidth;
    int max_frames_h = planet.height / frameheight;
    Vector2 navaPosition = {(float)0, (float)0};
    // Initialize shoots
    //--------------------------------------------------------------------------------------
    // for (int i = 0; i < NUM_SHOOTS; i++)
    // {
    //     shoot[i].start_poz.x = navaPosition.x;
    //     shoot[i].start_poz.y = navaPosition.y;
    //     shoot[i].end_poz.x = 5;
    //     shoot[i].rect.height = 10;
    //     shoot[i].speed.x = 0;
    //     shoot[i].speed.y = -10;
    //     shoot[i].active = false;
    //     shoot[i].color = MAROON;
    // }
    // //--------------------------------------------------------------------------------------
    // a line strip

    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawText(TextFormat("Mouse: %.1f, %.1f", GetMousePosition().x, GetMousePosition().y), 400, 10, 20, RED);
        DrawText(TextFormat("Screen Size: %i, %i", SCREEN_WIDTH, SCREEN_HEIGHT), 400, 30, 20, RED);

        if (IsKeyDown(KEY_D))
            navaPosition.x += 2.0f;
        if (IsKeyDown(KEY_A))
            navaPosition.x -= 2.0f;
        if (IsKeyDown(KEY_W))
            navaPosition.y -= 2.0f;
        if (IsKeyDown(KEY_S))
            navaPosition.y += 2.0f;

        ClearBackground(RAYBLACK);
        // DrawLineStrip(line,10,RED);
        timer += GetFrameTime();
        if (timer >= 0.02f)
        {
            frame++;
            if (frame >= max_frames_w)
            {
                frame2++;
            }
            timer = 0.0f;
        }
        frame = frame % max_frames_w;
        // if(frame2>=max_frames_h)
        // {
        //     frame2=0;
        // }
        frame2 = frame2 % max_frames_h;
        //   std::cout<<frame<<" "<<frame2<<std::endl;
        // DrawCircleV(Vector2{30,30},5,RED);
        draw_bg();
        // DrawLine(500, 900, GetMousePosition().x,GetMousePosition().y, RED);
        DrawFPS(10, 10);
        //print prssed variable
    
        DrawText(TextFormat("%d prssed",prssed), 700, 10, 20, RED);
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && prssed == 0)
        {
            prssed = 1;
            PlaySound(fxWav);
            mousepoz= GetMousePosition();
        }
        if (prssed == 1)
        {
            timer2 += GetFrameTime();
            if (timer2 >= 0.02f)
            {
                frame3++;
                timer2 = 0.0f;
            }
            if (frame3 < 40)
            {
                bullet(navaPosition, mousepoz);
            }
        }
        if (frame3 > 40)
        {
            prssed = 0;
            frame3 = 0;
            timer2 = 0.0f;
            bullets[0].len = 0;
        }
   
        float degrees = calculate_angle(navaPosition);
        DrawTexturePro(planet, Rectangle{framewidth * frame, frameheight * frame2, framewidth, frameheight}, Rectangle{SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, framewidth * 3, frameheight * 3}, Vector2{0.5, 0.5}, 0, WHITE);
        DrawTextureTiled(spaceship, Rectangle{framewidth_space * 5, 0, framewidth_space, frameheight_space}, Rectangle{navaPosition.x, navaPosition.y, framewidth_space, frameheight_space}, Vector2{0, 0}, degrees - 90, 1, WHITE);
        // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        // draw the spaceship at the angle calculated above

        EndDrawing();
    }

    CloseWindow();

    return 0;
}