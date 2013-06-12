#include "Class_Game.h"

int Game_Area::left=SCREEN_WIDTH*0.045;
int Game_Area::right=SCREEN_WIDTH-(SCREEN_WIDTH*0.13)-Game_Area::left;
int Game_Area::up=SCREEN_HEIGHT*0.02;
int Game_Area::bottom=SCREEN_HEIGHT-(SCREEN_HEIGHT*0.03)-Game_Area::up;
int Tank_source::tanks=0;
int Game_Area::map=MAX_MAP;

int Game_Area::tanks_limit=10;
bool Game_Area::game_over=false;
//-----------------------------------------------------------------------------------------------
Explode::Explode(int x, int y, int animID, int life_time):stand_Object(x,y,animID),life_time(life_time)
 {
  middle_x=x-w/2;
  middle_y=y-h/2;
  time=Timer();
 }
void Explode::update()
 {
  Helper=NULL;
  x=middle_x;
  y=middle_y;
  animate();
  if(time.time()>life_time)
   Dead=true;
 }
//-----------------------------------------------------------------------------------------------
void Shot::move()
{
 Helper=NULL;
 switch(direction)
 {
 case UP:
  vx=0; vy=-v;
 break;
 case DOWN:
  vx=0; vy=v;
 break;
 case LEFT:
  vx=-v; vy=0;
 break;
 case RIGHT:
  vx=v; vy=0;
 break;
 }
}
bool Shot::check_collision(GAME_Object *check){
  if( 
	  check->type()!=father_type &&
	  check!=my_helper && check!=father && check!=this && 
	  up<=check->bottom && left<=check->right && right>=check->left && bottom>=check->up 
	)
  {check->shot(strong); return true;}
  return false;
 }
void Shot::movecontact(int type){
 if(type!=TANK_SOURCE && type!=WATER && type!=FOREST && type!=EXPLODE && Helper==NULL)
 {
  Helper=new Explode(x,y,5,150);
  my_helper=Helper;
  Dead=true; 
 }
}
//-----------------------------------------------------------------------------------------------
void Player::move()
{
 Helper=NULL;
 if(Game_Area::game_over)
  changeAnim(0);
 if(time.time()>500 && !Game_Area::game_over && player_life>0)
 {
 if(EVENTS[K_UP])
  {vx=0; vy=-v; direction=UP; changeAnim(3); snd(2,1);}
 else if(EVENTS[K_LEFT])
  {vx=-v; vy=0; direction=LEFT; changeAnim(3); snd(2,1);}
 else if(EVENTS[K_DOWN])
  {vx=0; vy=v; direction=DOWN; changeAnim(3); snd(2,1);}
 else if(EVENTS[K_RIGHT])
  {vx=v; vy=0; direction=RIGHT; changeAnim(3); snd(2,1);}
 else
  {vx=0; vy=0; changeAnim(2); snd(1,1);}
 }
 else
 {vx=0;vy=0;}

switch(direction)
 {
 case UP:
  pozHelper_x=x+w/2-5; pozHelper_y=y;
 break;
 case DOWN:
  pozHelper_x=x+w/2-5; pozHelper_y=y+h;
 break;
 case LEFT:
  pozHelper_x=x; pozHelper_y=y+h/2-5;
 break;
 case RIGHT:
  pozHelper_x=x+w; pozHelper_y=y+h/2-5;
 break;
 }

 if(EVENTS[K_SPACE] && timeHelper.time()>500 && !Game_Area::game_over)
  {
   snd(3,2);
   timeHelper=Timer();
   Helper=new Shot(pozHelper_x,pozHelper_y,4,7,direction,this,1);
   my_helper=Helper;
  }
}

void Player::move2()
{
 Helper=NULL;
 if(Game_Area::game_over)
  changeAnim(0);
 if(time.time()>500 && !Game_Area::game_over && player_life>0)
 {
 if(EVENTS[W])
  {vx=0; vy=-v; direction=UP; changeAnim(39); snd(2,1);}
 else if(EVENTS[A])
  {vx=-v; vy=0; direction=LEFT; changeAnim(39); snd(2,1);}
 else if(EVENTS[S])
  {vx=0; vy=v; direction=DOWN; changeAnim(39); snd(2,1);}
 else if(EVENTS[D])
  {vx=v; vy=0; direction=RIGHT; changeAnim(39); snd(2,1);}
 else
  {vx=0; vy=0; changeAnim(38); snd(1,1);}
 }
 else
 {vx=0;vy=0;}

switch(direction)
 {
 case UP:
  pozHelper_x=x+w/2-5; pozHelper_y=y;
 break;
 case DOWN:
  pozHelper_x=x+w/2-5; pozHelper_y=y+h;
 break;
 case LEFT:
  pozHelper_x=x; pozHelper_y=y+h/2-5;
 break;
 case RIGHT:
  pozHelper_x=x+w; pozHelper_y=y+h/2-5;
 break;
 }

 if(EVENTS[P] && timeHelper.time()>500 && !Game_Area::game_over)
  {
   snd(3,2);
   timeHelper=Timer();
   Helper=new Shot(pozHelper_x,pozHelper_y,4,7,direction,this,1);
   my_helper=Helper;
  }
}

void Player::update()
{
 snd(0,0);
 Helper=NULL;
 
 if(player==1)
  move();
 else
  move2();

 old_x=x; old_y=y;
 x+=vx; y+=vy;

 animate(); 
 set_size();

 if(player_life<=0)
  {old_x=-100;x=-100;}

 if(shot_in)snd(4,3);

 if(time_shot.time()>50)
  shot_in=false;
 if (life<1)
 {
  player_life--;
  snd(5,4);
  Helper=new Explode(x+w/2,y+h/2,12,140);
  my_helper=Helper;
  old_x=start_x; old_y=start_y;
  x=start_x; y=start_y;
  time=Timer();
  life=1;
  changeAnim(13);
 }
}
//-----------------------------------------------------------------------------------------------
CPU1::CPU1(int x, int y, int CPU_type, int CPU_life):Tank(x,y,13,0,DOWN,CPU_life),CPU_type(CPU_type)
{
 time_move=Timer();
 switch(CPU_type)
 {
 case 1:
  v=3;
 break;
 case 2:
  v=5;
 break;
 case 3:
  v=2;
 break;
 default:
  v=4;
 }
}

void CPU1::movecontact(int type)
{
 Tank::movecontact(type);
 //course+=180;
 if(course<0 || course >360) course=0;
}

void CPU1::update()
{
 Tank::update();
 
 if(CPU_type==4)
  startAnim=32;
 else
 switch(life)
 {
 case 1:
  startAnim=14+(6*(CPU_type-1));
 break;
 case 2:
  startAnim=16+(6*(CPU_type-1));
 break;
 case 3:
  startAnim=18+(6*(CPU_type-1));
 break;
 }
}

void CPU1::move()
{
 if(time.time()>500)
 {
 if(time_move.time()>1000)
 {
  //if(x<player_x-100) course=K_RIGHT;
  //else if(x>player_x+100) course=K_LEFT;
  //else if(y<player_y-100) course=K_DOWN;
  //else if(y>player_y+100) course=K_UP;
  //else course=time_move.time()%2;

	int r = (rand() % 4) + 1;
	switch(r){
	case 1:course=K_RIGHT; break;
	case 2:course=K_LEFT; break;
	case 3:course=K_UP; break;
	default:course=K_DOWN; break;
	}

  time_move=Timer();
 }

 switch(course)
 {
 case K_UP:
  vx=0; vy=-v; direction=UP; changeAnim(startAnim+1);
 break;
 case K_LEFT:
  vx=-v; vy=0; direction=LEFT; changeAnim(startAnim+1);
 break;
 case K_DOWN:
  vx=0; vy=v; direction=DOWN; changeAnim(startAnim+1);
 break;
 case K_RIGHT:
  vx=v; vy=0; direction=RIGHT; changeAnim(startAnim+1);
 break;
 case NONE:
  vx=0; vy=0; changeAnim(startAnim);
 break;
 }
 }

 switch(direction)
 {
 case UP:
  pozHelper_x=x+w/2-5; pozHelper_y=y;
 break;
 case DOWN:
  pozHelper_x=x+w/2-5; pozHelper_y=y+h;
 break;
 case LEFT:
  pozHelper_x=x; pozHelper_y=y+h/2-5;
 break;
 case RIGHT:
  pozHelper_x=x+w; pozHelper_y=y+h/2-5;  
 break;
 }
 Helper=NULL;
 if((int(timeHelper.time()/1000))%2 && timeHelper.time()>500)
  {
   timeHelper=Timer();
   if(CPU_type!=3)
    Helper=new Shot(pozHelper_x,pozHelper_y,4,7,direction,this,1);
   else
    Helper=new Shot(pozHelper_x,pozHelper_y,4,7,direction,this,2);
   my_helper=Helper;
  }
}

void Steel::shot(int strong)
{
 shot_in=true;
 if(strong==2)
   Dead=true; 
}

void Steel::update()
{
 if(shot_in)
 {shot_in=false;}
 else
  snd(0,0);
}

void Brick::update()
{
  if(shot_in)
  {
   Dead=true;
   shot_in=false;
  }
}

void Eagle::update()
{
  animate(); 
  set_size();
  Helper=NULL;

  if(shot_in && animID==10)
  {
   changeAnim(11);
   Helper=new Explode(x+w/2,y+h/2,12,150);
   my_helper=Helper;
   shot_in=false;
   Game_Area::game_over=true;
  }
}

void Tank_source::update()
{
 move_Object::update();
 w=39; h=39;
 set_size();
 Helper=NULL;

 if(!stop && t.time()>500+rand()%500 && tanks<3 && Game_Area::tanks_limit>0)
 {
  Helper=new CPU1(x+1,y+1,1+rand()%4,1+rand()%3);
  tanks++;
  Game_Area::tanks_limit--;
  t=Timer();
  stop=true;
 }
 stop=false;
}

void Tank_source::movecontact(int type)
{
 if(type!=AREA)
  stop=true;
}

bool Tank_source::check_collision(GAME_Object *check){
  if(
	  check!=this && 
	  up<=check->bottom && left<=check->right && right>=check->left && bottom>=check->up 
	)
   return true;
  return false;
}

void Pointer::move()
{
 direction=RIGHT;
 changeAnim(3);

 if(EVENTS[K_UP] && time.time()>300)
  {
   y+=poz; time=Timer(); poz=-poz;
  }

 else if(EVENTS[K_DOWN] && time.time()>300)
  {
   y+=poz; time=Timer(); poz=-poz;
  }

 if(EVENTS[K_SPACE] && time.time()>300)
  {
   if(y==start_y) player_life=1;
   else player_life=2;
  }
}