#pragma once

// #include <Windows.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int FPS_LIMIT=60;
const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
const int SCREEN_BPP=32;
const int EVENTS_SIZE=11;

const int MAX_FIELD_X=22;
const int MAX_FIELD_Y=19;

const int MAX_MAP=5;

enum{UP=0, LEFT=90, DOWN=180, RIGHT=270, NONE=360,};
enum{END=0, K_LEFT=1, K_RIGHT=2, K_UP=3, K_DOWN=4, K_SPACE=5, W=6, A=7, S=8, D=9, P=10};
enum{INTRO, GAME1, GAME2};

struct sprite{
 int x ,y, w, h;
 sprite(int x, int y, int w, int h)
 {
  this->x=x; this->y=y;
  this->w=w; this->h=h;
 }
};

struct anim
{
 unsigned n;
 vector<int> spriteID;
 vector<int> spriteTime;
 anim(int n):n(n){}
};