#pragma once
#include "graf_Object.h"

enum {AREA, TANK_SOURCE, TANK, CPU, SHOT, STEEL, BRICK, WATER, FOREST, EAGLE, EXPLODE, OBJECT};

class GAME_Object: public graf_Object
{
protected:
 int snd_ID, snd_chanel;
 bool shot_in;
 bool Dead;

 GAME_Object *Helper, *my_helper;
 int pozHelper_x;
 int pozHelper_y; 
 Timer timeHelper;

 void set_size()
 {left=x; right=x+w; up=y; bottom=y+h;}
 void snd(int id,int chanel){snd_ID=id;snd_chanel=chanel;}

public:
 GAME_Object(int x, int y, int animID):graf_Object(x,y,animID),Dead(false),shot_in(false),snd_ID(0),Helper(NULL),my_helper(NULL)
 {set_size();}

 int left, right, up, bottom;

 int get_snd(){return snd_ID;}
 int get_snd_chanel(){return snd_chanel;}
 virtual int get_dir(){return 0;}
 virtual bool get_Dead(){return Dead;}
 virtual GAME_Object* get_helper(){return Helper;}
 virtual int type(){return OBJECT;}
 virtual bool get_move(){return false;}
 virtual int get_life(){return 0;}

 virtual void update(){}

 virtual void movecontact(int type){}

 virtual bool check_collision(GAME_Object *check){return false;}
 virtual void check_end_game_area(){}

 virtual void shot(int strong){shot_in=true;}
};