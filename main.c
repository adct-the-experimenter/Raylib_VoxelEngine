#include "raylib.h"
#include "player.h"
#include "world.h"
#include <string.h>

#define GLSL_VERSION 330

int main(void) {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;
    Color crosshairColor = (Color){ 0, 0, 0, 80 };

    InitWindow(screenWidth, screenHeight, "Game");
    SetTraceLogLevel(LOG_WARNING);
    SetTargetFPS(60);
    
    Block_Define(1, "stone", 1, 1, 1);
    Block_Define(2, "dirt", 2, 2, 2);
    Block_Define(3, "grass", 0, 2, 3);
    Block_Define(4, "wood", 4, 4, 4);
    
    Player player;
    Player_Init(&player);
    
    // World Initialization
    World_Init();
    
    Shader shader = LoadShader(TextFormat("chunk_shader.vs", GLSL_VERSION),
                               TextFormat("chunk_shader.fs", GLSL_VERSION));
    
    Image terrainTex = LoadImage("textures/terrain.png"); 
    Texture2D texture = LoadTextureFromImage(terrainTex);
    UnloadImage(terrainTex);
    
    World_ApplyTexture(texture);
    World_ApplyShader(shader);

    // Game loop
    while (!WindowShouldClose()) {
        
        // Update
        Player_Update(&player);
        
        // Draw
        BeginDrawing();

            ClearBackground((Color) { 140, 210, 240});

            BeginMode3D(player.camera);
                World_Draw(player.camera.position);
            EndMode3D();
            
            DrawFPS(16, 16);
            
            DrawRectangle(screenWidth / 2 - 8, screenHeight / 2 - 2, 16, 4, crosshairColor);
            DrawRectangle(screenWidth / 2 - 2, screenHeight / 2 + 2, 4, 6, crosshairColor);
            DrawRectangle(screenWidth / 2 - 2, screenHeight / 2 - 8, 4, 6, crosshairColor);

        EndDrawing();
    }
    
    UnloadShader(shader);
    UnloadTexture(texture);
    World_Unload();

    CloseWindow();

    return 0;
}