#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0)
    {
        // set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        // ternary operator - if(condition) ? do : else
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = running;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    // Draw the character
    Rectangle source{frame * width, 0.0f, rightLeft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(
        texture,    // Texture - where to find it
        source,    // section in the spritesheet where to get it
        dest,      // Position in the screen and size of the sprite
        Vector2{}, // Origin where is generated the image
        0.f,       // Rotation
        WHITE      // Color
    );
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}