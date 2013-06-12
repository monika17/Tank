#include "animObject.h"
#include "SDL.h"

void animObject::animate()
{
 if(animOLD!=animID)
  i_anim=0;

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