#pragma once
#include "stand_Object.h"
#include "move_Object.h"
#include "Tank.h"
#include <time.h>
#include <stdlib.h>

class Game_Area
{
public:
 static int tanks_limit;
 static int left, right, up, bottom;
 static bool game_over;
 static int map;
};

class Explode: public stand_Object
{
 Timer time;
 int life_time;
 int middle_x, middle_y;
public:
 Explode(int x, int y, int animID, int life_time);
 int type(){return EXPLODE;}
 void update();
};

class Shot: public move_Object
{ 
 GAME_Object* father;
 int father_type;
 void move();
 int strong;
public:
 Shot(int x, int y, int animID, int v, int dir, GAME_Object* father, int strong):move_Object(x,y,animID,v,dir),father(father),strong(strong)
 {father_type=father->type();}

 int type(){return SHOT;}

 bool check_collision(GAME_Object *check);
 void movecontact(int type);
};

class Player: public Tank
{
protected:
 vector<bool>::iterator EVENTS;
 void move();
 void move2();
 int start_x, start_y;
 int player;
 int player_life;
public:
 int get_life(){return player_life;}
 void update();
 Player(int x, int y, int animID, int v, int dir, int life, vector<bool>::iterator EVENTS,int player):Tank(x,y,animID,v,dir,1),EVENTS(EVENTS),player(player)
 {player_life=life; start_x=x; start_y=y;}
};

class CPU1: public Tank
{
 Timer time_move;
 int course;
 void move();
 void movecontact(int type);
 int CPU_type;
public:
 CPU1(int x, int y, int CPU_type, int CPU_life);
 void update();
 int type(){return CPU;}
};

class Steel: public stand_Object
{
public:
 Steel(int x, int y, int animID):stand_Object(x,y,animID){}
 int type(){return STEEL;}
 void shot(int strong);
 void update();
};

class Brick: public stand_Object
{
public:
 Brick(int x, int y, int animID):stand_Object(x,y,animID){}
 int type(){return BRICK;}
 void update();
};

class Water: public stand_Object
{
public:
 Water(int x, int y, int animID):stand_Object(x,y,animID){}
 int type(){return WATER;}
};

class Forest: public stand_Object
{
public:
 Forest(int x, int y, int animID):stand_Object(x,y,animID){}
 int type(){return FOREST;}
};

class Eagle: public stand_Object
{
public:
 Eagle(int x, int y, int animID):stand_Object(x,y,animID){}
 int type(){return EAGLE;}
 void update();
};

class Tank_source: public move_Object
{
 Timer t;
 bool stop;
public:
 static int tanks;
 Tank_source(int x, int y, int animID):move_Object(x,y,animID,0,0)
 {t=Timer(); stop=false; srand(time(NULL));}
 void update();
 void movecontact(int type);
 bool check_collision(GAME_Object *check);
 int type(){return TANK_SOURCE;}
};

class Pointer: public Player
{
 int poz;
public:
 void update(){animate();move();}
 void move();
 Pointer(int x, int y, int animID,vector<bool>::iterator EVENTS):Player(x,y,animID,0,RIGHT,0,EVENTS,1){poz=30;}
};