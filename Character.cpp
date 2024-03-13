#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) :
    windowWidth(winWidth),
    windowHeight(winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;
}

//Character position in the screen
Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),   // x
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)  // y
    };
}

void Character::tick(float deltaTime)
{
 

    if (IsKeyDown(KEY_A))
        velocity.x--;
    if (IsKeyDown(KEY_D))
        velocity.x++;
    if (IsKeyDown(KEY_W))
        velocity.y--;
    if (IsKeyDown(KEY_S))
        velocity.y++;

    BaseCharacter::tick(deltaTime);    

    //if character not alive, return will end before the other lines execute
    if(!getAlive()) return;
    //origin by where is generated
    Vector2 origin{};
    //offset = distance to sprite not cover the character sprite
    Vector2 offset{};
    //Rotation of the sword
    float rotation;
    if(rightLeft > 0.f)//facing right
    {
        origin = {0.f, weapon.height * scale};
        offset = {40.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
    }
    else
    {
        origin= {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
    }

    //Draw the sword
    //source = where find the texture in the sprite
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    //dest where to draw in the screen
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    DrawRectangleLines(
        weaponCollisionRec.x, weaponCollisionRec.y, weaponCollisionRec.width, weaponCollisionRec.height, RED
    );
}