#include <raylib.h>
#include "Game.hpp"

int main() 
{
    // const Color darkGreen = {20, 160, 133, 255};
    
    constexpr int screenWidth = 1000;
    constexpr int screenHeight = 700;

    
    
    
    InitWindow(screenWidth, screenHeight, "Flappy AI");
    SetTargetFPS(60);
    
    Game game;
    
    while (!WindowShouldClose())
    {
        
        BeginDrawing();
            float dt = GetFrameTime();
            
            game.Tick(dt);

            
        EndDrawing();
    }
    
    CloseWindow();
}