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
    Vector2 getScreenPos() {return screenPos;}
private:
    
};

#endif