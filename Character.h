#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    //Constructor
    Character(int winWidth, int winHeight);
    // gets the world position value
    Vector2 getWorldPos() { return worldPos; }
    // tick function
    void tick(float deltaTime);
    //Undo the movement if pass the map bounds
    void undoMovement();
    Rectangle getCollisionRec();

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")},
        idle{LoadTexture("characters/knight_idle_spritesheet.png")},
        running{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{}, worldPos{};
    Vector2 worldPosLastFrame{};
    // 1 : facing the right, -1 : facing the left
    float rightLeft{1.f};
    // Animation variables
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float width{}, height{};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float scale{4.0f};
};