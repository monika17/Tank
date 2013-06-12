#include "graf_Object.h"
#include <vector>

vector<sprite> graf_Object::sprites;
vector<anim> graf_Object::animDef;

bool graf_Object::newSprite(int id, int x, int y, int w, int h)
 {
  int n=sprites.size();
  if(id<n)
   return 0;
  sprites.resize(id+1,sprite(x,y,w,h));
  return 1;
 }

bool graf_Object::newAnim(int id, int n)
 {
  int size=animDef.size();
  if(id<size)
   return 0;
  animDef.resize(id+1,(anim(n)));
  return 1;
 }

bool graf_Object::addFrame(int animID, int sprID, int t)
 {
  animDef[animID].spriteID.push_back(sprID); 
  animDef[animID].spriteTime.push_back(t);
  return 1;
 }

void graf_Object::animate()
{
 if(animOLD!=animID)
  i_anim=0;

 if(animID<0 || animID>animDef.size()-1 || animDef.empty())
  throw "Nie ma takiej animacji!";
 if(animDef[animID].n>animDef[animID].spriteTime.size())
  throw "Blad definicji animacji w pliku cfg!";

  if(getTimeAnim)
  {
   timeAnim=Timer(); 
   getTimeAnim=false;
  }
  if(timeAnim.time() >= animDef[animID].spriteTime[i_anim])
  {
   i_anim++; 
   if(i_anim>=animDef[animID].n)
	i_anim=0; 
   getTimeAnim=true;
  }

 spriteID=animDef[animID].spriteID[i_anim];

  w=sprites[spriteID].w;
  h=sprites[spriteID].h;
}
