/********************************************************************************************
    @filename:    rmpd.c
    @title:       Real Pixel Lighting RAMP DEMO
    @description: Simple gradient demo of RPL with shadows
    @author:      Samy Bencherif
    Copyright (C) 2020 Samy Bencherif (@deathstallion)
    Permission is hereby granted, free of charge, to any person obtaining a copy of this
    software and associated documentation files (the "Software"), to deal in the Software
    without restriction, including without limitation the rights to use, copy, modify,
    merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to the following
    conditions:
    The above copyright notice and this permission notice shall be included in all copies
    or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
    INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
    PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
    CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
    THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    This program has been created using raylib 1.0 (www.raylib.com)
    raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
    Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
********************************************************************************************/
//#include "raymath.h"
#include "raylib.h"

#include <math.h>

// Constants
//--------------------------------------------------------------------------------------
const int screenWidth = 128;
const int screenHeight = 128;
const int scaleFactor = 3;
//--------------------------------------------------------------------------------------

int withinRect(int tx, int ty, int x, int y, int w, int h)
{
  return (tx > x) && (tx < x + w) && (ty > y) && (ty < y + h);
}

void PixRect(int x, int y, int w, int h, Color c)
{
   DrawRectangle(scaleFactor * x, scaleFactor * y, scaleFactor * w, scaleFactor * h, c);
}

int main(void)
{
  // Initialization
  //--------------------------------------------------------------------------------------
  int clock = 0;

  InitWindow(screenWidth * scaleFactor, screenHeight * scaleFactor, "Real Pixel Lighting");

  SetTargetFPS(30);         // Set our game framerate
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    // Update
    clock ++;

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

      ClearBackground(WHITE);

      int mouseX = GetMouseX() / scaleFactor;
      int mouseY = GetMouseY() / scaleFactor;


      int RW = 10;
      int RH = 10;
      int RX = mouseX - RW / 2;
      int RY = mouseY - RH / 2;

      for (int x = 0; x < screenWidth; x ++)
      {
        for (int y = 0; y < screenHeight; y ++)
        {
          Vector2 lightSrc = CLITERAL(Vector2){screenWidth/2, screenHeight/2};
          Vector2 screenPos = CLITERAL(Vector2){x,y};

          const float flickerRate = 4;
          const float flickerAmp = .003;

          const float intensity = .4 + flickerAmp * sin(clock * flickerRate);
          const float range = .95;

          const float bounceRate = .9;
          const float gi = .3;

         // float d = Vector2Distance(lightSrc, screenPos);
          int b = 255*intensity - d/range;
          if (b < 0) b = 0;

          float emission = 1;

          float samples = 100;
          for (int i=0; i<samples; i++)
          {
            float testX = screenWidth/2 + (x - screenWidth/2) * i/samples;
            float testY = screenHeight/2 + (y - screenHeight/2) * i/samples;

            if (withinRect(testX, testY, RX, RY, RW, RH))
            {
              emission *= bounceRate;
            }
          }

          b =  gi * b + (1 - gi) * b * emission;

          Color c = CLITERAL(Color){ b, b, b, 255 };

          PixRect(x, y, 1, 1, c );
        }
      }

      PixRect(mouseX, mouseY, 1, 1, BLUE);
      PixRect(RX, RY, RW, RH, RED);



    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();    // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}