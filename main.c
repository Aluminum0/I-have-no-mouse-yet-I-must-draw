

/*******************************************************************************************
*
*   raylib [shapes] example - lines drawing
*
*   Example originally created with raylib 6.0, last time updated with raylib 5.6
*
*   Example contributed by Robin (@RobinsAviary) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2025 Robin (@RobinsAviary)
*
*
********************************************************************************************/

#include "raylib.h"
#include "stdio.h"
#include "raymath.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [forked] - Happy birthday!");

    // Hint text that shows before you click the screen
    bool startText = true;

    // The mouse's position on the previous frame
    Vector2 mousePositionPrevious = GetMousePosition();

    // The canvas to draw lines on
    RenderTexture canvas = LoadRenderTexture(screenWidth, screenHeight);

    // The line's thickness
    float lineThickness = 8.0f;
    // The lines hue (in HSV, from 0-360)
    float lineHue = 0.0f;

    // Clear the canvas to the background color
    BeginTextureMode(canvas);
        ClearBackground(BLACK);
    EndTextureMode();

    SetTargetFPS(60);

    //music
    InitAudioDevice();
    Music CORE = LoadMusicStream("music/mus_core.ogg");
    printf("Current Directory: %s\n", GetWorkingDirectory());
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateMusicStream(CORE);

        if (IsKeyPressed(KEY_H))
                {
                    if (IsCursorHidden()) ShowCursor();
                    else HideCursor();
                }
        // Update
        //----------------------------------------------------------------------------------
        // Disable the hint text once the user clicks
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && startText) startText = false;

        // Clear the canvas when the user middle-clicks
        if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
        {
            BeginTextureMode(canvas);
                ClearBackground(BLACK);
            EndTextureMode();
        }

        // Store whether the left and right buttons are down
        bool leftButtonDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        bool rightButtonDown = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);

        if (leftButtonDown || rightButtonDown)
        {
            // The color for the line
            Color drawColor = WHITE;

            if (leftButtonDown)
            {
                // Create the final color
                drawColor = WHITE;
            }
            else if (rightButtonDown) drawColor = BLACK; // Use the background color as an "eraser"

            // Draw the line onto the canvas
            BeginTextureMode(canvas);
                // Circles act as "caps", smoothing corners
                DrawCircleV(mousePositionPrevious, lineThickness/2.0f, drawColor);
                DrawCircleV(GetMousePosition(), lineThickness/2.0f, drawColor);
                DrawLineEx(mousePositionPrevious, GetMousePosition(), lineThickness, drawColor);
            EndTextureMode();
        }

        // Update line thickness based on mousewheel
        lineThickness += GetMouseWheelMove();
        lineThickness = Clamp(lineThickness, 1.0, 500.0f);

        // Update mouse's previous position
        mousePositionPrevious = GetMousePosition();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            // Draw the render texture to the screen, flipped vertically to make it appear top-side up
            DrawTextureRec(canvas.texture, (Rectangle){ 0.0f, 0.0f, (float)canvas.texture.width,(float)-canvas.texture.height }, Vector2Zero(), WHITE);

            // Draw the preview circle
            if (!leftButtonDown) DrawCircleLinesV(GetMousePosition(), lineThickness/2.0f, (Color){ 127, 127, 127, 127 });

            //
            if (IsKeyPressed(KEY_B)) DrawCircleLinesV(GetMousePosition(), lineThickness/2.0f, (Color){ 127, 127, 127, 127 });
            if (IsKeyPressed(KEY_M)){PlayMusicStream(CORE);}
            if (IsKeyPressed(KEY_P)) PauseMusicStream(CORE);
            if (IsKeyPressed(KEY_R)) ResumeMusicStream(CORE);
            if (IsKeyPressed(KEY_S)) StopMusicStream(CORE);
            if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S)) {
                TakeScreenshot("screenshot.png");
                TraceLog(LOG_INFO, "SCREENSHOT TAKEN!");
            }
            // Draw the hint text
            if (startText) DrawText("Happy Birthday! try clicking and dragging!", 150, 155, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    UnloadMusicStream(CORE);
    CloseAudioDevice();
    UnloadRenderTexture(canvas); // Unload the canvas render texture
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

  }
