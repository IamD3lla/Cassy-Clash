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
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());

    //BaseCharacter::tick(deltaTime);
}

//set the screen position of the enemy
Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}