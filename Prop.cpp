#include "Prop.h"

//This way, worldPos will be initialized with the value of pos before the execution of the body
Prop::Prop(Vector2 pos, Texture2D tex) : 
    worldPos(pos),
    texture(tex)
{

}