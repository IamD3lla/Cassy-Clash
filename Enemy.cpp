#include "Enemy.h"
#include "raymath.h"

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

    speed = 3.5f;
}

void Enemy::tick(float deltaTime)
{
    //get toTargert - toTarget is the vector between the enemy to the target(character)
    Vector2 toTarget = Vector2Subtract(target->getScreenPos(), screenPos);
    //Normalize toTarget
    toTarget = Vector2Normalize(toTarget);
    //Multiply toTarget by speed
    toTarget = Vector2Scale(toTarget, speed);
    //Move the enemy to the character
    worldPos = Vector2Add(worldPos, toTarget);
    //set the screen position of the enemy
    screenPos = Vector2Subtract(worldPos, target->getWorldPos());

    BaseCharacter::tick(deltaTime);
}