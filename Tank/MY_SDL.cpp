#include "MY_SDL.h"
#include <algorithm>

SDL::SDL(string caption, string fontType, int fontSize):screen(NULL),sheet(NULL),printText(NULL),font(NULL),keystates(NULL)
 {
  if(SDL_Init(SDL_INIT_EVERYTHING)==-1)
	throw "Blad inicjalizacji biblioteki SDL";

  SDL_WM_SetCaption(caption.c_str(),NULL);
  screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);

  if(TTF_Init()==-1)
	throw "Blad inicjalizacji biblioteki SDL_ttf";
  font=TTF_OpenFont(fontType.c_str(),fontSize);

  if(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 )==-1)
   throw "Blad inicjalizacji biblioteki SDL_mixer";

  keystates = SDL_GetKeyState(NULL);

  if(!screen || !font || !keystates)
   throw "Blad inicjalizacji biblioteki SDL";
 }

void SDL::setSheet(string sheet_name, int R, int G, int B)
{
 sheet=loadImg(sheet_name,R,G,B);
}

SDL_Surface *SDL::loadImg(string file, int R, int G, int B)
{
 SDL_Surface* loadedImage=NULL;
 SDL_Surface* optimizedImage=NULL;

 loadedImage=SDL_LoadBMP(file.c_str());
 if(loadedImage!=NULL)
 {
  optimizedImage = SDL_DisplayFormat( loadedImage );
  SDL_FreeSurface(loadedImage);
 
  if(optimizedImage!=NULL)
   SDL_SetColorKey(optimizedImage,SDL_SRCCOLORKEY,SDL_MapRGB(optimizedImage->format,R,G,B));
 }
 return optimizedImage;
}

void SDL::events(vector<bool>&EVENTS)
{
 while(SDL_PollEvent(&event))
 {
  if(event.type==SDL_QUIT)
   EVENTS[END]=true;

  if(event.type==SDL_KEYDOWN)
   {
	switch( event.key.keysym.sym )
    {
      case SDLK_UP: EVENTS[K_UP]=true; break;
      case SDLK_DOWN: EVENTS[K_DOWN]=true; break;
      case SDLK_LEFT: EVENTS[K_LEFT]=true; break;
      case SDLK_RIGHT: EVENTS[K_RIGHT]=true; break;
	  case SDLK_SPACE: EVENTS[K_SPACE]=true; break;

      case SDLK_w: EVENTS[W]=true; break;
      case SDLK_s: EVENTS[S]=true; break;
      case SDLK_a: EVENTS[A]=true; break;
      case SDLK_d: EVENTS[D]=true; break;
	  case SDLK_p: EVENTS[P]=true; break;
    }
   }
  if(event.type==SDL_KEYUP)
   {
	switch( event.key.keysym.sym )
    {
      case SDLK_UP: EVENTS[K_UP]=false; break;
      case SDLK_DOWN: EVENTS[K_DOWN]=false; break;
      case SDLK_LEFT: EVENTS[K_LEFT]=false; break;
      case SDLK_RIGHT: EVENTS[K_RIGHT]=false; break;
	  case SDLK_SPACE: EVENTS[K_SPACE]=false; break;

      case SDLK_w: EVENTS[W]=false; break;
      case SDLK_s: EVENTS[S]=false; break;
      case SDLK_a: EVENTS[A]=false; break;
      case SDLK_d: EVENTS[D]=false; break;
	  case SDLK_p: EVENTS[P]=false; break;
    }
   }
 }
}

void SDL::print(int x, int y, string text, int R, int G, int B)
 {
  SDL_Color textColor={R,G,B};
  printText=TTF_RenderText_Solid(font,text.c_str(),textColor);
  SDL_Rect dest;
  dest.x=x; dest.y=y;
  SDL_BlitSurface(printText,NULL,screen,&dest);
  SDL_FreeSurface(printText);
 }
void SDL::print(int x, int y, int X, int R, int G, int B)
 {
  SDL_Color textColor={R,G,B};
  ostringstream txt;
  txt<<X;
   printText=TTF_RenderText_Solid(font,txt.str().c_str(),textColor);
  SDL_Rect dest;
  dest.x=x; dest.y=y;
   SDL_BlitSurface(printText,NULL,screen,&dest);
   SDL_FreeSurface(printText);
 }

void SDL::draw_fill_rect(int x, int y, int w, int h, int R, int G, int B)
{
 SDL_Rect src;
 src.x=x; src.y=y; src.w=w; src.h=h;
 SDL_FillRect(screen,&src,SDL_MapRGB(screen->format, R, G, B));
}

void SDL::draw(sprite *spr, int x, int y)
 {
 SDL_Rect src;

 src.x=spr->x;
 src.y=spr->y;
 src.w=spr->w;
 src.h=spr->h;

 SDL_Rect dst;
 dst.x=x; dst.y=y;

  SDL_BlitSurface(sheet,&src,screen,&dst);
}
void SDL::draw(sprite *spr, int x, int y, int rotate)
{
 SDL_Surface *temp2=NULL;

 SDL_Rect src;
 src.x=spr->x; src.y=spr->y;
 src.w=spr->w; src.h=spr->h;
 
 SDL_Rect dst;
 dst.x=x; dst.y=y;

 temp = SDL_CreateRGBSurface(SDL_ANYFORMAT,src.w,src.h,sheet->format->BitsPerPixel,0,0,0,0);
 temp->w=src.w;
 temp->h-src.h;
 if(temp!=NULL)
 {
  SDL_BlitSurface(sheet,&src,temp,NULL);

  temp2=rotozoomSurface(temp,rotate,1,0);

  SDL_SetColorKey(temp2, SDL_SRCCOLORKEY, SDL_MapRGB( temp->format, 0, 0, 0 ) );
  SDL_BlitSurface(temp2,NULL,screen,&dst);
   SDL_FreeSurface(temp);
   SDL_FreeSurface(temp2);
 }
}

bool SDL::add_SND(int ID, string file)
{
 int n=sounds.size();
 if(ID<n)
  return 0;

 Mix_Chunk *temp=NULL;
 temp=Mix_LoadWAV(file.c_str());
 if(!temp)return 0;

 sounds.resize(ID+1,temp);
 return 1;
}

void SDL::play_snd(int id, int chanel)
{
 if(id<0 || id>sounds.size()-1 || sounds.empty())
  throw "nie ma takiego dzwieku!";
 Mix_PlayChannel( chanel, sounds[id], 0 );
}

void clear_snd(Mix_Chunk *snd)
{
 Mix_FreeChunk(snd);
}

SDL::~SDL()
 {
  SDL_FreeSurface(sheet);

  for_each(sounds.begin(),sounds.end(),clear_snd);
  Mix_CloseAudio();
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_Quit();
 }