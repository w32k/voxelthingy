
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <stdio.h>
#include <stdbool.h>
#define WORLD_SIZE 20


bool box[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE] = {0};

int main(){
    for(int x = 0; x < WORLD_SIZE; x++){
        for(int y = 0; y < WORLD_SIZE; y++){
            for(int z = 0; z < WORLD_SIZE; z++){
                box[x][y][z] = true;
            }
        }
    }
    InitWindow(1600, 900, "Cube");
    Camera3D cam = {
        .position = (Vector3){
            2.0, 25, 2.0
        },
        .target = (Vector3){
            0, 0, 0
        },
        .up = (Vector3){
            0, 1, 0
        },
        .fovy = 90,
        .projection = CAMERA_PERSPECTIVE
    };
    rlEnableBackfaceCulling();
    DisableCursor();
    while(!WindowShouldClose()){
        UpdateCamera(&cam, CAMERA_FREE);
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(cam);
        int idk = 255 / WORLD_SIZE;
        for(int i = 0; i < WORLD_SIZE; i++){
            for(int j = 0; j < WORLD_SIZE; j++){
                for(int z = 0; z < WORLD_SIZE; z++){
                    if(box[i][j][z] == false) continue;
                    // bad collision system, idk
                    Vector3 position = { (float)i, (float)j, (float)z };
                    BoundingBox b = {
                        (Vector3){ position.x - 0.27f, position.y - 0.27f, position.z - 0.27f },
                        (Vector3){ position.x + 0.27f, position.y + 0.27f, position.z + 0.27f }
                    };
                    Vector2 screenCenter = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
                    Ray ray = GetScreenToWorldRay(screenCenter, cam);
                    Color color = {i * idk, j * idk, z * idk, 255};
                    RayCollision collision = GetRayCollisionBox(ray, b);
                    if(collision.hit){
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                            box[i][j][z] = false;
                        }
                        DrawCubeWires(position, 1, 1, 1, WHITE);
                        color.a = 120;
                    }
                    CubeFaces cube = 0;

                    if(i == 0){
                        cube |= FACE_LEFT;
                    } else if(i == WORLD_SIZE -1){
                        cube |= FACE_RIGHT;
                    }
                    if(box[i-1][j][z] == false && i > 0){
                        cube |= FACE_LEFT;
                    } else if(box[i+1][j][z] == false && i < WORLD_SIZE){
                        cube |= FACE_RIGHT;
                    }
                    if(j == 0){
                        cube |= FACE_BOTTOM;
                    } else if(j == WORLD_SIZE -1){
                        cube |= FACE_TOP;
                    }
                    if(box[i][j-1][z] == false && j > 0){
                        cube |= FACE_BOTTOM;
                    } else if(box[i][j+1][z] == false && j < WORLD_SIZE){
                        cube |= FACE_TOP;
                    }
                    if(z == 0){
                        cube |= FACE_BACK;
                    } else if(z == WORLD_SIZE -1){
                        cube |= FACE_FRONT;
                    }
                    if(box[i][j][z-1] == false && z > 0){
                        cube |= FACE_BACK;
                    } else if(box[i][j][z+1] == false && z < WORLD_SIZE){
                        cube |= FACE_FRONT;
                    }
                    DrawCubeOptimized(position, 1, 1, 1, cube, color);
                    //DrawCube(position, 1, 1, 1, color);

                }
            }
        }
        EndMode3D();
        DrawRectangleV((Vector2){GetScreenWidth()/2.0f, GetScreenHeight()/2.0f}, (Vector2){10.0f, 10.0f}, WHITE);
        DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
