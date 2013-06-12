#pragma once
#include "move_Object.h"

class Tank: public move_Object
{
protected:
 int life;
 Timer time, time_shot;
 int startAnim;
public:
 static int player_x;
 static int player_y;

 Tank(int x, int y, int animID, int v, int dir, int life):move_Object(x,y,animID,v,dir),life(life)
 {time=Timer(); startAnim=animID; this->animID=13; time_shot=Timer();}
 
 int get_life(){return life;}
 int type(){return TANK;}

 virtual bool check_collision(GAME_Object *check);

 void movecontact(int type);

 void update();
 void shot(int strong)
 {
  if(!shot_in){life--; time_shot=Timer();} shot_in=true; 
 }
};