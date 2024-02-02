#include "raylib.h"
#include "raymath.h"

class Character {
    public:
        //gets the world position value
        Vector2 getWorldPos(){return worldPos;}
    private:
        Texture2D texture, idle, running;
        Vector2 screenPos, worldPos;
        //1 : facing the right, -1 : facing the left
        float rightLeft{1.f};
        //Animation variables
        float runningTime{};
        int frame{};
        const int maxFrames{6};
        const float updateTime{1.f/12.f};
};

int main(){

    //Window Dimensions
    const int windowDimension{384};

    InitWindow(windowDimension, windowDimension, "Cassy Clash!");

    //Note = A texture can't be loaded before there is a window to load it
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    //Map position
    Vector2 mapPos{0,0};
    //movement speed of the player - Secret tip: the map is moving
    float speed{4};

    //Knight 
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    //Knight idle
    Texture2D knightIdle = LoadTexture("characters/knight_idle_spritesheet.png");
    //Knight running
    Texture2D knightRun = LoadTexture("characters/knight_run_spritesheet.png");
    //Location of the knight upper left corner
    Vector2 knightPos{
        //Multiplied by 4 because it's scaled 4 times
        (float)windowDimension/2.0f - 4.0f * (0.5f * (float)knightIdle.width/6.0f), // x
        (float)windowDimension/2.0f - 4.0f * (0.5f * (float)knightIdle.height) //y
    };

    //1 : facing the right, -1 : facing the left
    float rightLeft{1.f};
    //Animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f/12.f};

    SetTargetFPS(60);
    while(!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};
        if(IsKeyDown(KEY_A)) direction.x--;
        if(IsKeyDown(KEY_D)) direction.x++;
        if(IsKeyDown(KEY_W)) direction.y--;
        if(IsKeyDown(KEY_S)) direction.y++;

        if(Vector2Length(direction) != 0){
            //set mapPos = mapPos - direction
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
            //ternary operator - if(condition) ? do : else
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            knight = knightRun;
        }else {
            knight = knightIdle;
        }

        //Draw the map
        DrawTextureEx(map, mapPos, 0, 4, WHITE);

        //update animation frame
        runningTime += GetFrameTime();
        if(runningTime >= updateTime){
            frame++;
            runningTime = 0.f;
            if(frame > maxFrames) frame = 0;
        }

        //Draw the character
        Rectangle source{frame * (float)knight.width/6.f, 0.0f, rightLeft * (float)knight.width/6.f, (float)knight.height};
        Rectangle dest{knightPos.x, knightPos.y, 4.0f * (float)knight.width/6.0f, 4.0f * (float)knight.height};
        DrawTexturePro(
            knight, //Texture - where to find it
            source, //section in the spritesheet where to get it
            dest, //Position in the screen and size of the sprite
            Vector2{}, //Origin where is generated the image
            0.f, //Rotation
            WHITE //Color
        );

        EndDrawing();

    }
    UnloadTexture(knight);
    UnloadTexture(knightRun);
    UnloadTexture(knightIdle);
    CloseWindow();

}