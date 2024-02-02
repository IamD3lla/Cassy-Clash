#include "raylib.h"

int main(){

    //Window Dimensions
    const int windowDimension{384};

    InitWindow(windowDimension, windowDimension, "Cassy Clash!");

    //Note = A texture can't be loaded before there is a window to load it
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");

    SetTargetFPS(60);
    while(!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(WHITE);

        //Draw the map
        Vector2 mapPos{0,0};
        DrawTextureEx(map, mapPos, 0, 4, WHITE);

        EndDrawing();

    }
    CloseWindow();

}