//if the symbol is not defined executes
//this type of "if" is started before the program starts
#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    //Constructor
    Character(int winWidth, int winHeight);
    // tick function
    //virtual key allows to override the parent function tick
    //override key says that this funtion is overriding the function from the parent
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec() {return weaponCollisionRec;}
private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec;
};

#endif