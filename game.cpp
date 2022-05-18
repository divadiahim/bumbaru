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
struct bullet
{
    float len = 10;
    float offset = 1;
};
struct bullet bullets[100];
float o1 = 0.005;
float l1 = 15;
float l2 = 6;
Rectangle rect1;
bool check_collided(Vector2 poz1, int rad1, Vector2 poz2, int rad2)
{
    bool planet_collision = CheckCollisionCircles(poz1, rad1, poz2, rad2);
    return planet_collision;
}
Vector2 bam;
Vector2 bam2;
bool ok = false;
void bullet(Vector2 navaPosition, Vector2 mousePosition)
{
    static int offset = 1;
    bool planet_collision = false;
    Vector2 start_pos = {navaPosition.x, navaPosition.y};
    Vector2 end_pos = {mousePosition.x, mousePosition.y};
    Vector2 poz_3 = Vector2Normalize(Vector2Subtract(end_pos, start_pos));

    // print len and offset
    DrawLineEx(start_pos, Vector2Add(start_pos, poz_3), 10, RED);
    for (int i = 0; i < 1; i++)
    {
        bullets[i].len += l1;
        //   std::cout << bullets[i].len << " " << bullets[i].offset << std::endl;
        poz_3.x *= bullets[i].len;
        poz_3.y *= bullets[i].len;
        Vector2Normalize(start_pos);

        if (ok)
            DrawCircleV(Vector2Add(start_pos, poz_3), 10, RED);
        bam = Vector2Add(start_pos, poz_3);

        // check_collided(Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},170,Vector2Add(start_pos, poz_3),10);
    }
}
bool prssed = 0;
void planet_boss(Vector2 ship_poz)
{
    Vector2 start_pos = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    Vector2 end_pos = {ship_poz.x, ship_poz.y};
    Vector2 poz_3 = Vector2Normalize(Vector2Subtract(end_pos, start_pos));
    bullets[1].len += l2;
    poz_3.x *= bullets[1].len;
    poz_3.y *= bullets[1].len;
    Vector2Normalize(start_pos);
    DrawCircleV(Vector2Add(start_pos, poz_3), 10, YELLOW);
    bam2 = Vector2Add(start_pos, poz_3);
}
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitAudioDevice();
    Sound fxWav = LoadSound("../assets/sf_laser_15.mp3");
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] game - gravitas");
    Texture2D planet = LoadTexture("../assets/planets.png");
    Texture2D spaceship = LoadTexture("../assets/spaceship.png");
    Texture2D asteroid = LoadTexture("../assets/asteroid.png");
    Font font = LoadFont("../assets/pcsenior.ttf");
    int_bg();
    SetTargetFPS(144);
    //--------------------------------------------------------------------------------------
    // draw a black background
    // variable-initialization
    //--------------------------------------------------------------------------------------
    float lives_no = 3;
    bool lost = false;
    bool won = false;
    int lives_planet = 30;
    float framewidth = planet.width / 50;
    float frameheight = planet.height / 4;
    float framewidth_space = spaceship.width / 18;
    float frameheight_space = spaceship.height / 10;
    float timer = 0.0f;
    int frame = 0;
    int frame2 = 0;
    float timer2 = 0.0f;
    int frame3 = 0;
    int frame4 = 0;
    float timer3 = 0;
    Vector2 mousepoz;
    int max_frames_w = planet.width / framewidth;
    int max_frames_h = planet.height / frameheight;
    bool planet_collision = false;
    bool spaceship_collision = false;
    bool last_state = false;
    bool current_state = false;
    bool current_state2 = false;
    bool last_state2 = false;
    bool stop = false;
    float cooldown = 80;
    Vector2 navaPosition = {(float)0, (float)0};
    Vector2 nava_static;
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())
    {
        BeginDrawing();
        if (!lost)
        {
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
            // print prssed variable

            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && prssed == 0)
            {
                prssed = 1;
                PlaySound(fxWav);
                mousepoz = GetMousePosition();
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
                ok = 1;
                bullets[0].len = 0;
            }

            timer3 += GetFrameTime();
            if (timer3 >= 0.02f)
            {
                frame4++;
                timer3 = 0.0f;
            }
            if (frame4 < cooldown)
            {
                planet_boss(nava_static);
            }
            if (frame4 > cooldown)
            {
                prssed = 0;
                frame4 = 0;
                timer3 = 0.0f;
                bullets[1].len = 0;
                nava_static = navaPosition;
                PlaySound(fxWav);
            }

            // help me overcome my depression+ge
            std::cout << bullets[1].len << " " << frame4 << " " << std::endl;
            DrawTextEx(font, TextFormat("Lives %f", lives_no), Vector2{780, 10}, 30, 1, Color{255, 255, 255, 255});
            DrawRectangleRoundedLines(Rectangle{750, 100, 230, 50}, 0.7, 4, 4, Color{70, 52, 235, 255});
            DrawRectangleRounded(Rectangle{750, 100, (230 / 30) * (float)lives_planet, 50}, 0.7, 4, Color{70, 52, 235, 255});
            planet_collision = check_collided(Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, 170, bam, 10);
            spaceship_collision = check_collided(Vector2Add(navaPosition, Vector2{10, 0}), 35, bam2, 10);

            current_state2 = spaceship_collision;
            lives_no = (current_state2 == last_state2) ? lives_no : (float)lives_no - 0.5f;
            last_state2 = current_state2;

            DrawText(TextFormat("%d Collided", spaceship_collision), 700, 200, 20, RED);
            current_state = planet_collision;
            // random value between 0 and 1
            float rand1 = (planet_collision) ? (((float)rand() / (float)RAND_MAX) / 1) * (1 - 0.85) + 0.85 : 1;
            float rand2 = (planet_collision) ? (((float)rand() / (float)RAND_MAX) / 1) * (1 - 0.85) + 0.85 : 1;
            lives_planet = (current_state && !last_state) ? lives_planet - 1 : lives_planet, last_state = current_state;
            if (planet_collision)
                ok = 0;
            float degrees = calculate_angle(navaPosition);


            DrawTexturePro(planet, Rectangle{framewidth * frame, frameheight * frame2, framewidth, frameheight}, Rectangle{(SCREEN_WIDTH / 3) * (rand1), (SCREEN_HEIGHT / 3) * (rand2), framewidth * 3, frameheight * 3}, Vector2{0.5, 0.5}, 0, WHITE);
            DrawTextureTiled(spaceship, Rectangle{framewidth_space * 5, 0, framewidth_space, frameheight_space}, Rectangle{navaPosition.x, navaPosition.y, framewidth_space, frameheight_space}, Vector2{0, 0}, degrees - 90, 1, WHITE);
            DrawTexturePro(asteroid, Rectangle{(float)(asteroid.width/50)*frame, (float)(asteroid.height), (float)asteroid.width/50, (float)asteroid.height}, Rectangle{SCREEN_WIDTH / 8, SCREEN_HEIGHT / 8, (float)asteroid.width/50, (float)asteroid.height}, Vector2{0.5, 0.5}, 0, WHITE);
            DrawTexturePro(asteroid, Rectangle{(float)(asteroid.width/50)*frame, (float)(asteroid.height), (float)asteroid.width/50, (float)asteroid.height}, Rectangle{SCREEN_WIDTH / 1.3, SCREEN_HEIGHT / 1.5, (float)asteroid.width/50, (float)asteroid.height}, Vector2{0.5, 0.5}, 0, WHITE);
            DrawTexturePro(asteroid, Rectangle{(float)(asteroid.width/50)*frame, (float)(asteroid.height), (float)asteroid.width/50, (float)asteroid.height}, Rectangle{SCREEN_WIDTH / 8, SCREEN_HEIGHT / 1.3, (float)asteroid.width/50, (float)asteroid.height}, Vector2{0.5, 0.5}, 0, WHITE);
            DrawTexturePro(asteroid, Rectangle{(float)(asteroid.width/50)*frame, (float)(asteroid.height), (float)asteroid.width/50, (float)asteroid.height}, Rectangle{SCREEN_WIDTH / 1.2, SCREEN_HEIGHT / 8, (float)asteroid.width/50, (float)asteroid.height}, Vector2{0.5, 0.5}, 0, WHITE);
            if(lives_planet<22) cooldown = cooldown - 0.01f;
        
        
        }
        if (lives_no == 0)
        {
            lost = true;
            ClearBackground(GRAY);
            DrawText("You Lost!", SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, 60, RED);
        }
        if (lives_planet == 0)
        {
            won = true;
            lost = true;
        }
        if (won)
        {
            ClearBackground(GRAY);
            DrawText("You won!", SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, 60, RED);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}