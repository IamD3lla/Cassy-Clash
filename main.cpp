#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    // gets the world position value
    Vector2 getWorldPos() { return worldPos; }
    void setScreenPos(int winWidth, int winHeight);
    // tick function
    void tick(float deltaTime);

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")},
        idle{LoadTexture("characters/knight_idle_spritesheet.png")},
        running{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{}, worldPos{};
    // 1 : facing the right, -1 : facing the left
    float rightLeft{1.f};
    // Animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};
    const float speed{4.f};
};

// Makes reference to the character class
void Character::setScreenPos(int winWidth, int winHeight)
{
    //Character position in the screen
    screenPos = {
        // Multiplied by 4 because it's scaled 4 times
        (float)winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f), // x
        (float)winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)       // y
    };
}

void Character::tick(float deltaTime)
{

    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x--;
    if (IsKeyDown(KEY_D))
        direction.x++;
    if (IsKeyDown(KEY_W))
        direction.y--;
    if (IsKeyDown(KEY_S))
        direction.y++;

    if (Vector2Length(direction) != 0)
    {
        // set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        // ternary operator - if(condition) ? do : else
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = running;
    }
    else
    {
        texture = idle;
    }

    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    // Draw the character
    Rectangle source{frame * (float)texture.width / 6.f, 0.0f, rightLeft * (float)texture.width / 6.f, (float)texture.height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * (float)texture.width / 6.0f, 4.0f * (float)texture.height};
    DrawTexturePro(
        texture,    // Texture - where to find it
        source,    // section in the spritesheet where to get it
        dest,      // Position in the screen and size of the sprite
        Vector2{}, // Origin where is generated the image
        0.f,       // Rotation
        WHITE      // Color
    );
}

int main()
{

    // Window Dimensions
    const int windowDimension{384};

    InitWindow(windowDimension, windowDimension, "Cassy Clash!");

    // Note = A texture can't be loaded before there is a window to load it
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    // Map position
    Vector2 mapPos{0, 0};

    Character knight;
    knight.setScreenPos(windowDimension, windowDimension);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(WHITE);

        //Vector2Scale multiplies the first value by the second
        //This function is fliping the map by the oposite side of the player to movement
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw the map
        DrawTextureEx(map, mapPos, 0, 4, WHITE);

        knight.tick(GetFrameTime());
    
        EndDrawing();
    }
    CloseWindow();
}