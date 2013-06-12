#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_rotozoom.h>
#include "SDL_mixer.h"
#include "head.h"

class SDL
{
private:
 SDL_Surface *screen, *sheet, *printText, *temp;
 TTF_Font *font;
 SDL_Event event;
 Uint8 *keystates;
 vector<Mix_Chunk*> sounds;

 SDL_Surface *loadImg(string file, int R=255, int G=0, int B=255);
public:
 SDL(string caption, string fontType="arial.ttf", int fontSize=14);

 void setSheet(string sheet_name, int R=255, int G=0, int B=255);

 void events(vector<bool>&EVENTS);
 
 void draw_fill_rect(int x, int y, int w, int h, int R, int G, int B);

 void draw(sprite *spr, int x, int y);
 void draw(sprite *spr, int x, int y, int rotate);

 void print(int x, int y, string text, int R=255, int G=255, int B=255);
 void print(int x, int y, int X, int R=255, int G=255, int B=255);

 bool add_SND(int ID, string file);
 void play_snd(int id, int chanel);

 void update()
 {
  SDL_Flip(screen);
  SDL_FillRect(screen,&screen->clip_rect,SDL_MapRGB(screen->format, 0, 0, 0));
 }
 ~SDL();
};