#pragma once
#include <SDL.h>
#include "head.h"

class Timer
{
private:
 int start, loop, tempTime, tempFPS, fps, countFPS;
public:
 Timer()
 {
  start=SDL_GetTicks(); loop=0; tempTime=0; tempFPS=0; fps=0; countFPS=0;
 }
 int time(int d=1)
 {
  return (SDL_GetTicks()-start)/d;
 }
 void startLoop(int d=1)
 {
  loop=SDL_GetTicks();
  if(loop/1000 != tempTime/1000)
  {fps=countFPS; countFPS=0; }
  tempTime=SDL_GetTicks();
  countFPS++;
 }
 int timeLoop(int d=1)
 {
  return (SDL_GetTicks()-loop)/d;
 }
 int get_fps()
 { return fps; }
 void limit(int n)
 {
  if(timeLoop() < 1000/n)
   SDL_Delay(( 1000/FPS_LIMIT ) - timeLoop());
 }
};