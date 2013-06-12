#pragma once
#include "head.h"
#include "MY_SDL.h"
#include "Timer.h"

class GAME_Object;
class move_Object;
class stand_Object;

void message(string caption, string txt);

class Tank_Game
{
private:
 bool game;
 unsigned state;

 int field_size;

 SDL sdl;
 bool loadFiles(string file_name);

 vector<bool> EVENTS;

 bool game_over;
 bool game_start;
 bool intro_start;

 void show(GAME_Object* temp);

 GAME_Object *P1, *P2, *eagle, *logo, *logo2, *menu, *pointer;
 vector<GAME_Object*> helpers, forest, game_objects;
 vector<GAME_Object*>::iterator object, check, delete_object;

 bool del;

 bool load_maps(int maps_id);
 int _i(int i);
 int _j(int j);
 bool map_reserved(int x, int y, int i, int j);

public:
 Tank_Game():sdl("Tanki"),field_size(24)
 {
  game=true;
  state=INTRO;
  intro_start=true;
  game_start=true;
  EVENTS.resize(EVENTS_SIZE,false);
  del=false;
  game_over=false;
  i_map=0;

  if(!loadFiles("cfg.txt"))
   throw "Blad czytania pliku cfg.txt";
  P1=NULL; P2=NULL; eagle=NULL; menu=NULL; logo=logo2=pointer=NULL;
 }
 void stmControl(int bufferX, int bufferY, int bufferB);
 void debug(int fps, int time);
 unsigned game_state(){return state;}

 int i_map;
 void intro();
 void play_game(int game_type);

 void update();
 bool operator ! (){return game;}
 ~Tank_Game();
};

