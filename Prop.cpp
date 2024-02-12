#include "Prop.h"
#include "raymath.h"

//This way, worldPos will be initialized with the value of pos before the execution of the body
Prop::Prop(Vector2 pos, Texture2D tex) : 
    worldPos(pos),
    texture(tex)
{

}

void Prop::render(Vector2 knightPos) 
{
    //Set the position of the prop in the screen
    Vector2 screenPos{Vector2Subtract(worldPos, knightPos)};
    //Draw the texture
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}

Rectangle Prop::getCollisionRec(Vector2 knightPos)
{
    Vector2 screenPos{Vector2Subtract(worldPos, knightPos)};
    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width * scale,
        texture.height * scale
    };
}