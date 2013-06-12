#include "Class_Game.h"
#include "head.h"

void message(string caption, string txt)
{
 // MessageBox( NULL, txt.c_str(), caption.c_str(), MB_OK | MB_ICONEXCLAMATION );
}

bool Tank_Game::loadFiles(string file_name)
 {
  ifstream cfg(file_name.c_str());
  string line;

  if(!cfg)
   return 0;
  else while(getline(cfg,line))
  {
    stringstream temp(line);
    while(!temp.eof())
    {
     string word;
     temp>>word;
     if(word==";") 
      break;
     else if(word=="SPRITE")
     {
      int id=0; temp>>id;
      int x=1; temp>>x;
      int y=1; temp>>y;
      int w=1; temp>>w;
      int h=1; temp>>h;
       if(!graf_Object::newSprite(id,x,y,w,h))
		return 0;
      break;
     }
 	 else if(word=="SHEET_COLOR_KEY") 
	 {
	  int R=0; temp>>R;
	  int G=0; temp>>G;
      int B=0; temp>>B;
       sdl.setSheet("sheet.bmp",R,G,B);
  	 }
	 else if(word=="ANIM")
	 {
	  int id=0; temp>>id;
	  int n=0; temp>>n;
	   if(!graf_Object::newAnim(id,n))
		return 0;
	 }
	 else if(word=="ADD_FRAME")
	 {
	  int animID=0; temp>>animID;
	  int sprID=0; temp>>sprID;
	  int t=1; temp>>t;
	   if(!graf_Object::addFrame(animID,sprID,t))
		return 0;
	 }
	 else if(word=="SOUND")
	 {
	  int snd_ID=0; temp>>snd_ID;
	  string snd_file=" "; temp>>snd_file;
	  if(!sdl.add_SND(snd_ID,snd_file))
	   return 0;
	 }
    }
   }
   cfg.close();

  return 1;
 }

void Tank_Game::show(GAME_Object* temp)
{
   sprite tmp_sprite = temp->get_sprite();
   sdl.draw(&tmp_sprite,temp->get_x(),temp->get_y(),temp->get_dir());
}

int Tank_Game::_i(int i){return Game_Area::left+(i)*field_size;}
int Tank_Game::_j(int j){return Game_Area::up+(j)*field_size;}

void Tank_Game::intro()
{
 if(intro_start)
 {
  game_start=true;
  Game_Area::game_over=false; game_objects.clear();
  logo=new GAME_Object(30,10,1);
  logo2=new GAME_Object(150,120,40);
  menu=new GAME_Object(200,260,41);
  pointer=new Pointer(150,250,2,EVENTS.begin());
  intro_start=false;
 }

 pointer->update();
 show(logo);
 show(logo2);
 show(menu);
 show(pointer);
 switch(pointer->get_life())
 {
 case 1:
  state=GAME1;
 break;
 case 2:
  state=GAME2;
 break;
 }
}

void Tank_Game::play_game(int game_type)
{
 intro_start=true; 
 if(game_start)
 {
  sdl.play_snd(0,-1);
  Game_Area::game_over=false; game_objects.clear();

  game_objects.push_back(new Brick(_i(9),_j(18),6));
  game_objects.push_back(new Brick(_i(12),_j(18),6));
  game_objects.push_back(new Brick(_i(9),_j(17),6));
  game_objects.push_back(new Brick(_i(12),_j(17),6));
  game_objects.push_back(new Brick(_i(9),_j(16),6));
  game_objects.push_back(new Brick(_i(12),_j(16),6));
  game_objects.push_back(new Brick(_i(10),_j(16),6));
  game_objects.push_back(new Brick(_i(11),_j(16),6));

  game_objects.push_back(new Tank_source(_i(0),_j(0),0));
  game_objects.push_back(new Tank_source(_i(10)+1,_j(0),0));
  game_objects.push_back(new Tank_source(_i(20)+1,_j(0),0));
  P1=new Player(_i(7)+1,_j(17)+1,3,4,UP,3,EVENTS.begin(),1);
  if(game_type!=1)
   P2=new Player(_i(13)+1,_j(17)+1,38,4,UP,3,EVENTS.begin(),2);
  eagle=new Eagle( _i(10),_j(17),10);

  load_maps(i_map);

  game_objects.push_back(P1);
  if(game_type!=1)
   game_objects.push_back(P2);
  game_objects.push_back(eagle);

  Game_Area::tanks_limit=10;
  Tank_source::tanks=0;

  game_objects.push_back(new GAME_Object(570,100,34));

  game_start=false;
 }

 sdl.draw_fill_rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,101,101,101);
 sdl.draw_fill_rect(Game_Area::left,Game_Area::up,Game_Area::right,Game_Area::bottom,0,0,0);

 sdl.print(610,100,Game_Area::tanks_limit);
 sdl.print(565,140,"P1 life: ",0,0,0);
 sdl.print(614,140,P1->get_life());
 if(game_type==2)
 {
  sdl.print(565,180,"P2 life: ",0,0,0);
  sdl.print(614,180,P2->get_life());
 }

 for(object=game_objects.begin();object<game_objects.end();object++)
 {
 if(P1->get_life()>0)
 {
  Tank::player_x=P1->get_x();
  Tank::player_y=P1->get_y();
 }
 else if(game_type!=1)
 {
  Tank::player_x=P2->get_x();
  Tank::player_y=P2->get_y();
 }

  if(game_type==2 && P1->get_life()<=0 && P2->get_life()<=0)
   Game_Area::game_over=true;
  else if(game_type==1 && P1->get_life()<=0)
   Game_Area::game_over=true;

  if(Game_Area::game_over && !game_over)
  {helpers.push_back(new GAME_Object(215,400,37)); game_over=true;}

  if( (*object)->get_Dead() )
  {delete_object=object; del=true;}

  if( (*object)->get_helper() )
   helpers.push_back( (*object)->get_helper() );

  (*object)->update();

  if( (*object)->get_snd() )
   sdl.play_snd((*object)->get_snd(),(*object)->get_snd_chanel());
  
  if((*object)->get_move())
  (*object)->check_end_game_area();

  if((*object)->get_move())
  for(check=game_objects.begin();check<game_objects.end();check++)
  {
   if( (*object)->check_collision(*check))
	(*object)->movecontact( (*check)->type() );
  }

  if( (*object)->type()!=FOREST )
   show(*object);
  else
   forest.push_back(*object);
 }
 for(object=forest.begin();object<forest.end();object++)show(*object);
 forest.clear();

 if(del)
 {
  if( (*delete_object)->type()==CPU )
   Tank_source::tanks--;
   delete *delete_object;
  game_objects.erase(delete_object);
 }
 del=false;

 for(object=helpers.begin(); object<helpers.end();object++)
  game_objects.push_back(*object);
 helpers.clear();

 if(Game_Area::game_over && EVENTS[K_SPACE])
  state=INTRO;

 if(Game_Area::tanks_limit<=0 && Tank_source::tanks<=0 && EVENTS[K_SPACE])
 {
  i_map++;
  if(i_map>=MAX_MAP)i_map=0;
  if(game_type==1)
   state=GAME1;
  else state=GAME2;
  game_start=true;
 }

}

void Tank_Game::stmControl(int bufferX, int bufferY, int bufferB){

	EVENTS[K_RIGHT]=false;
	EVENTS[K_LEFT]=false;
	EVENTS[K_UP]=false;
	EVENTS[K_DOWN]=false;
	EVENTS[K_SPACE]=false;

	if(abs(bufferX) > 10 || abs(bufferY) >10)
	{

	if(abs(bufferX) > abs(bufferY)){
		if(bufferX < 0)
			EVENTS[K_RIGHT] = true;
		else
			EVENTS[K_LEFT] = true;
	}
	else{
		if(bufferY < 0)
			EVENTS[K_DOWN] = true;
		else
			EVENTS[K_UP] = true;
		}
    }
	if(bufferB)
		EVENTS[K_SPACE]=true;
}

void Tank_Game::debug(int fps, int time)
{
  sdl.print(577,10,"fps :",255,132,0);
  sdl.print(610,10,fps);
  sdl.print(565,23,"Time :",255,132,0);
  sdl.print(610,23,time);
  sdl.print(610,36,Tank_source::tanks);
  sdl.print(610,49,Game_Area::tanks_limit);
}

void Tank_Game::update()
{ 
 sdl.update();
 sdl.events(EVENTS);
 if(EVENTS[END]) game=false;
}

Tank_Game::~Tank_Game()
{
 //if(P1)delete P1;
}

bool Tank_Game::map_reserved(int x, int y, int i, int j)
{
 return (x>=_i(i) && x<_i(i+1) && y>=_j(j) && y<_j(j+1));
}

bool Tank_Game::load_maps(int maps_id)
{
  ifstream maps("maps.txt");
  string line;

  bool read=false;
  int j=0;

  if(!maps)
   return 0;
  else while(getline(maps,line))
  {
    stringstream temp(line);

	 if(read)
	 {
      for(int i=0; i<line.length(); i++)
	  {
	   int x=_i(i-1);
	   int y=_j(j);
       if(
		   !map_reserved(x,y,0,0) && !map_reserved(x,y,0,1) && !map_reserved(x,y,1,0) && !map_reserved(x,y,1,1) &&
		   !map_reserved(x,y,10,0) && !map_reserved(x,y,10,1) && !map_reserved(x,y,11,0) && !map_reserved(x,y,11,1) &&
		   !map_reserved(x,y,20,0) && !map_reserved(x,y,20,1) && !map_reserved(x,y,21,0) && !map_reserved(x,y,21,1) && 
		   !map_reserved(x,y,7,17) && !map_reserved(x,y,7,18) && !map_reserved(x,y,8,17) && !map_reserved(x,y,8,18) &&
		   !map_reserved(x,y,9,17) && !map_reserved(x,y,9,18) && !map_reserved(x,y,10,17) && !map_reserved(x,y,10,18) &&
		   !map_reserved(x,y,11,17) && !map_reserved(x,y,11,18) && !map_reserved(x,y,12,17) && !map_reserved(x,y,12,18) &&
		   !map_reserved(x,y,13,17) && !map_reserved(x,y,13,18) && !map_reserved(x,y,14,17) && !map_reserved(x,y,14,18) &&
		   !map_reserved(x,y,9,16) && !map_reserved(x,y,10,16) && !map_reserved(x,y,10,16) && !map_reserved(x,y,11,16) && !map_reserved(x,y,12,16)
		 )
	   {
	    if(line[i]=='B')
	   	 game_objects.push_back(new Brick(x,y,6));
	    if(line[i]=='S')
		 game_objects.push_back(new Steel(x,y,7));
	    if(line[i]=='W')
		 game_objects.push_back(new Water(x,y,8));
	    if(line[i]=='F')
		 game_objects.push_back(new Forest(x,y,9));
	   }
	  }
	  j++;
	  if(j>=MAX_FIELD_Y+2) read=false;
	 }

    while(!temp.eof())
    {
     string word;
     temp>>word;

     if(word==";") 
      break;
     else if(word=="ID")
     {
	  j=-1;
      int id=0; temp>>id;
      if(id==maps_id)
	   read=true;
	  else
	   read=false;
	 }
    }
   }
   maps.close();

  return 1;
}