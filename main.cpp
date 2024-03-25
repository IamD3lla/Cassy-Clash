#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

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
        Vector2{800.f, 300.f}, 
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")
    };

    Enemy* enemies[]{
        &goblin,
        &slime
    };

    for(auto enemy : enemies)
    {
        // "&" = addres of operator, gets the addres in the variable
        enemy->setTarget(&knight);
    }

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

        //Draw the props
        for (auto prop : props)
        {
            prop.render(knight.getWorldPos());
        }

        //Checks if the character is Alive
        if(!knight.getAlive()) //   Character is not alive
        {
            DrawText("Game Over!", 55.f, 45.f, 40.f, RED);
            EndDrawing();
            //continue is a c++ keyword that ignores the remaining part of the loop
            //and executes from the start again
            continue;
        }
        else // Character is alive
        {
            //creates a string
            std::string knightsHealth = "Health: ";
            //append() is used to append a value to the end of the string
            //to_string converts an integer value to a string       /starts from character 0 and shows 5
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40.f, RED);
        }

        knight.tick(GetFrameTime());

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
        
        //loop through the enemies
        for(auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for(auto enemy : enemies)
            {
                if(CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }
    CloseWindow();
}