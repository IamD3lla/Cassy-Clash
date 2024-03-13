#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

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

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}
    };

    Enemy goblin{
        Vector2{}, 
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };
    // "&" = addres of operator, gets the addres in the variable
    goblin.setTarget(&knight);

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

        //Draw the props
        for (auto prop : props)
        {
            prop.render(knight.getWorldPos());
        }

        //Check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowDimension > map.width * mapScale ||
            knight.getWorldPos().y + windowDimension > map.height * mapScale)
        {
            knight.undoMovement();
        }
    
        for(auto prop : props)
        {
            if(CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }
        
        goblin.tick(GetFrameTime());

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if(CheckCollisionRecs(goblin.getCollisionRec(), knight.getWeaponCollisionRec()))
            {
                goblin.setAlive(false);
            }
        }

        EndDrawing();
    }
    CloseWindow();
}