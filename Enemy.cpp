#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture) //:
    //Can only use this method to declare the variables if they belong only to the class and not to the
    //father class
    /*worldPos(pos),
    texture(idle_texture),
    idle(idle_texture),
    running(run_texture)*/
{

    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    running = run_texture;

    width = texture.width / maxFrames;
    height = texture.height;
}

void Enemy::tick(float deltaTime)
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