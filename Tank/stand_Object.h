#pragma once
#include "GAME_Object.h"
#include "move_Object.h"

class stand_Object: public GAME_Object
{
protected:
 int left, right, up, bottom;

 void set_size()
 {left=x; right=x+w; up=y; bottom=y+h;}
public:

 int type(){return OBJECT;}

 stand_Object(int x, int y, int animID):GAME_Object(x,y,animID)
 {set_size();}
};