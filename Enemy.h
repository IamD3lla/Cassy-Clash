#include "raylib.h"
#include "BaseCharacter.h"

class Enemy : public BaseCharacter
{
    public:
        Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
        Vector2 getWorldPos() { return worldPos; }
        void tick(float deltaTime);
        void undoMovement();
        Rectangle getCollisionRec();
    private:
        Texture2D texture{LoadTexture("characters/goblin_idle_spritesheet.png")},
                idle{LoadTexture("characters/goblin_idle_spritesheet.png")},
                running{LoadTexture("characters/goblin_run_spritesheet.png")};
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