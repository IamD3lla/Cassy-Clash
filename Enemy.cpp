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
    BaseCharacter::tick(deltaTime);
}