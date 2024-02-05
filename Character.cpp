#include "Character.h"
#include "raymath.h"

Character::Character()
{
    width = texture.width / maxFrames;
    height = texture.height;
}

// Makes reference to the character class
void Character::setScreenPos(int winWidth, int winHeight)
{
    //Character position in the screen
    screenPos = {
        // Multiplied by 4 because it's scaled 4 times
        (float)winWidth / 2.0f - 4.0f * (0.5f * width), // x
        (float)winHeight / 2.0f - 4.0f * (0.5f * height)       // y
    };
}

void Character::tick(float deltaTime)
{

    worldPosLastFrame = worldPos;

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
    Rectangle source{frame * width, 0.0f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * width, 4.0f * height};
    DrawTexturePro(
        texture,    // Texture - where to find it
        source,    // section in the spritesheet where to get it
        dest,      // Position in the screen and size of the sprite
        Vector2{}, // Origin where is generated the image
        0.f,       // Rotation
        WHITE      // Color
    );
}

void Character::undoMovement() 
{
    worldPos = worldPosLastFrame;
}