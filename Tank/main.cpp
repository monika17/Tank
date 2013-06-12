#include "Tank_Game.h"
#include "Timer.h"
#include "stdafx.h"
#include "hid.h"

int main(int argc, char* argv[])
{

  char buffer_in[64];
  for (int i=0;i<64;i++)
		buffer_in[i]=0;
  FindTheHID();

 try
 {
  Tank_Game tanki;
  Timer fps;

  while(!tanki)
  {
   fps.startLoop();

   ReadInputReport(buffer_in);
   tanki.stmControl(buffer_in[2],buffer_in[1],buffer_in[3]);

   switch(tanki.game_state())
   {
   case INTRO:
	tanki.intro();
   break;
   case GAME1:
	tanki.play_game(1);
   break;
   case GAME2:
	tanki.play_game(2);
   break;
   }
  // tanki.debug(fps.get_fps(),fps.time(1000));
   tanki.update();
  // tanki.menu();
  // do{
  // tanki.game(tanki.stage);
  // tanki.summary();
  // }while(tanki.gameOver());
   fps.limit(FPS_LIMIT);
  }
 }
 catch(char* error_init)
 {
  message("Error", error_init);
  return -1;
 }
 catch(...)
 {
  message("Error", "nieokreslony blad");
  return 1;
 }

 return 0;
}