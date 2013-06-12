#include "move_Object.h"
#include "stand_Object.h"
#include "Class_Game.h"

 move_Object::move_Object(int x, int y, int animID, int v, int dir):GAME_Object(x,y,animID), v(v), direction(dir)
 {
  pozHelper_x=0; pozHelper_y=0; timeHelper;
  vx=0; vy=0;
  old_x=x; old_y=y;
 }

 void move_Object::update()
 {
  Helper=NULL;
  move();
  old_x=x; old_y=y;
  x+=vx; y+=vy;
  animate(); 
  set_size();
 }

 void move_Object::check_end_game_area()
 {
  if(left<=Game_Area::left || right>=Game_Area::right+Game_Area::left || up<=Game_Area::up || bottom>=Game_Area::bottom+Game_Area::up)
   movecontact(AREA);
 }