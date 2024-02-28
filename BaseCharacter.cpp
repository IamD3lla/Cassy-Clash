#include "BaseCharacter.h"

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

    // Draw the character
    Rectangle source{frame * width, 0.0f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
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
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale
    };
}