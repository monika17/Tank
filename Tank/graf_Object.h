#pragma once
#include "head.h"
#include "Timer.h"
#include "Tank_Game.h"

class graf_Object
{
protected: 
 int x,y,w,h;

 static vector<sprite> sprites;
 static vector<anim> animDef;

 int spriteID;

 int animID, animOLD;
 Timer timeAnim;
 unsigned  i_anim;

 void animate();

 bool getTimeAnim;
 void changeAnim(int id){animOLD=animID; animID=id;}

public:
 graf_Object(int x, int y, int animID):x(x), y(y), animID(animID)
{
 i_anim=0;
 getTimeAnim=true;
 animOLD=animID;
 animate();
}

 int get_x(){return x;}
 int get_y(){return y;}

 sprite get_sprite(){return sprites[spriteID];}

 static bool newSprite(int id, int x, int y, int w, int h);
 static bool newAnim(int id, int n);
 static bool addFrame(int animID, int sprID, int t);

 void update()
 {
  animate();
 }
};
