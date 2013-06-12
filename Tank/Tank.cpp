#include "Tank.h"
#include "Class_Game.h"

int Tank::player_x=0;
int Tank::player_y=0;

bool Tank::check_collision(GAME_Object *check){
  if(
	  check!=my_helper && check!=this && 
	  up<=check->bottom && left<=check->right && right>=check->left && bottom>=check->up 
	)
   return true;
  return false;
}

void Tank::movecontact(int type){
  switch(type)
  {
  case CPU:
   x=old_x; y=old_y;
  case EAGLE:
   x=old_x; y=old_y;
  break;
  case AREA:
   x=old_x; y=old_y;
  break;
  case TANK:
   x=old_x; y=old_y;
  break;
  case STEEL:
   x=old_x; y=old_y;
  break;
  case BRICK:
   x=old_x; y=old_y;
  break;
  case WATER:
   x=old_x; y=old_y;
  break;
  }
}

void Tank::update()
{
snd(0,0);
 move_Object::update();
 if(shot_in)snd(4,3);
 if(time_shot.time()>50)
  shot_in=false;
 if (life<1)
 {
  snd(5,4);
  Helper=new Explode(x+w/2,y+h/2,12,140);
  my_helper=Helper;
  Dead=true;
 }
}