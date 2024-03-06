//if the name is not defined, will create the code
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
    public:
        BaseCharacter();
        //virtual allows the child classes to override the function
        virtual void tick(float deltaTime);
        // gets the world position value
        Vector2 getWorldPos() { return worldPos; }
        //This is a Pure virtual function, they're equaled to zero ;D
        virtual Vector2 getScreenPos() = 0;
        //Undo the movement if pass the map bounds
        void undoMovement();
        Rectangle getCollisionRec();
    protected:
        Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")},
                idle{LoadTexture("characters/knight_idle_spritesheet.png")},
                running{LoadTexture("characters/knight_run_spritesheet.png")};
        Vector2 worldPos{};
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
        //direction of the movement and distance that should move
        Vector2 velocity{};

};

#endif