#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    //Constructor
    Character(int winWidth, int winHeight);
    // tick function
    virtual void tick(float deltaTime) override;
private:
    
};