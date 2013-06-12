#pragma once
#include "GAME_Object.h"

class stand_Object;

class move_Object: public GAME_Object
{
protected:
 int old_x, old_y;
 int v, vx, vy;

 int direction;

 virtual void move(){}

public:
 move_Object(int x, int y, int animID, int v, int dir);

 bool get_move(){return true;}

 int get_dir(){return direction;}
 GAME_Object* get_helper(){return Helper;}

 void check_end_game_area();

 void update();
};