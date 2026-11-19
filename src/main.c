
#include "raylib.h"
#include "rlgl.h"
#include "blocks.h"
#define WORLD_SIZE 20



int main(){

    InitWindow(800, 600, "Cube");
    Camera3D cam = {
        .position = (Vector3){
            0.0, 0.0, 3.0
        },
        .target = (Vector3){
            0, 0, 0.0
        },
        .up = (Vector3){
            0, 1, 0
        },
        .fovy = 90,
        .projection = CAMERA_PERSPECTIVE
    };
    Texture2D blockTextures = LoadTexture("assets/blocks.png");
    Texture2D itemTextures = LoadTexture("assets/items.png");
    DisableCursor();
    while(!WindowShouldClose()){
        UpdateCamera(&cam, CAMERA_FREE);
        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginMode3D(cam);
        for(int i = 1; i < BLOCK_END_OF_ENUM; i++){
            draw_block(blockTextures, i, (Vector3){i - 1, 0.0f, 0.0f}, 1.0f, 1.0f, 1.0f);
        }
        // for(int i = 1; i < BLOCK_END_OF_ENUM; i++){
        //     draw_block(blockTextures, i, (Vector3){i - 1, 0.0f, 0.0f}, 1.0f, 1.0f, 1.0f);
        // }
        EndMode3D();
        DrawRectangleV((Vector2){GetScreenWidth()/2.0f, GetScreenHeight()/2.0f}, (Vector2){10.0f, 10.0f}, WHITE);
        DrawFPS(10, 10);
        DrawTexturePro(itemTextures, (Rectangle){16.0f, 0.0f, 16.0f, 16.0f}, (Rectangle){100.0f, 100.0f, 100.0f, 100.0f},
                                    (Vector2){0.0f, 0.0f}, 0.0f, ORANGE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
