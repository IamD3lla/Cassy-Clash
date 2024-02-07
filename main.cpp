#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{

    // Window Dimensions
    const int windowDimension{384};
    InitWindow(windowDimension, windowDimension, "Cassy Clash!");

    // Note = A texture can't be loaded before there is a window to load it
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    // Map position
    Vector2 mapPos{0, 0};
    //Map scale
    const float mapScale{4.0};

    Character knight{windowDimension, windowDimension};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(WHITE);

        //Vector2Scale multiplies the first value by the second
        //This function is fliping the map by the oposite side of the player to movement
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw the map
        DrawTextureEx(map, mapPos, 0, mapScale, WHITE);

        knight.tick(GetFrameTime());

        //Check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowDimension > map.width * mapScale ||
            knight.getWorldPos().y + windowDimension > map.height * mapScale)
        {
            knight.undoMovement();
        }
    
        EndDrawing();
    }
    CloseWindow();
}