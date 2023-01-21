/*
*
* GXRF Framework for SDL2 in C lang
*
*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <inttypes.h>
#include <time.h>
#include <stdarg.h>

#ifdef _WIN32
  #include <windows.h>
  #define getpid _getpid 
#elif LINUX
  #include <unistd.h>
  #define SDL_main main
  #define _MAX_PATH 256
#endif

#define FALSE 0

int gbRunning = TRUE;

char gszLogTitle[_MAX_PATH];

typedef void (*GXRFCALLBACK)(SDL_Renderer *renderer, ...);

void vTraceMsg(char *szMsg){
   FILE *pfLog;
  time_t lTime;
  struct tm *st_tm_Now;
  char szDateTimeNow_us[128];
  // struct timeval tv;
  time (&lTime);
  st_tm_Now = localtime(&lTime);
  // mingw_gettimeofday(&tv, NULL);

  memset(szDateTimeNow_us, 0, sizeof(szDateTimeNow_us));
  sprintf(szDateTimeNow_us,
    "[%02d/%02d/%04d %02d:%02d:%02d] ",
    (int)st_tm_Now->tm_mday, 
    (int)st_tm_Now->tm_mon+1, 
    (int)st_tm_Now->tm_mday,
    (int)st_tm_Now->tm_hour,
    (int)st_tm_Now->tm_min,
    (int)st_tm_Now->tm_sec
  );  

  if ( (pfLog=fopen(gszLogTitle, "a+")) == NULL )
    return;

  fprintf(pfLog, "%s", szMsg);

  fclose(pfLog);
}

typedef struct STRUCT_GXRF_RENDER{
  void *vSDL_ObjToRender;
  int iSDL_RenderType;
  GXRFCALLBACK vpfnRenderMethod;
  SDL_Renderer *pSDL_Renderer;
  va_list *vargRenderArgs;
  struct STRUCT_GXRF_RENDER *pNextObj;
}STRUCT_GXRF_RENDER;

STRUCT_GXRF_RENDER *gpstGXRF_Render;

enum SDLTypes{
  SDL_RECT = 1,
  SDL_IMAGE,
  SDL_TTF,
  SDL_TEXTURE
}eWndRose;


int iGXRF_Init(){
  return ( gpstGXRF_Render == NULL ) ? -1 : 0;
}

void vInitRenderList(SDL_Renderer *renderer, void *vRenderObject, int iSDL_RenderType, void* vpfnRenderFnc, va_list* vFncArgs){
  
  gstSDLRender.iSDL_RenderType  = iSDL_RenderType;
  gstSDLRender.vSDL_ObjToRender =  vRenderObject;
  gstSDLRender.vpfnRenderMethod =  vpfnRenderFnc;
  gstSDLRender.pSDL_Renderer    =   renderer;
  gstSDLRender.vargRenderArgs   =  vFncArgs;
}

void vRenderObjectFromList(void *vRenderObject, ...){
  // for() // whenever its gpstSDLRender->vSDL_ObjToRender == vRenderObject
  
  // SDL_SetRenderDrawColor(gstSDLRender.pSDL_Renderer, 255, 0, 0, 255); 
  gstSDLRender.vpfnRenderMethod(gstSDLRender.pSDL_Renderer, gstSDLRender.vargRenderArgs);

}

#define VSYNC_TIME 16.666666666 //tempo em ms para atualização em 60 FPS
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800
#define DEBUG_MSGS 1
#define DEBUG_MORE_MSGS 9
int SDL_main(int argc, char *argv[]){
  int iXTranslation = 0;
  uint64_t ui64ElapsedTime;
  SDL_Window* window;
  SDL_Renderer* renderer;
  char *pTok;
  
  sprintf(gszLogTitle, "%s", argv[0]);
  if ( (pTok = strstr(gszLogTitle, ".exe")) != NULL ){
    *pTok = 0;
  }
  strcat(gszLogTitle, ".log");

  vTraceMsg("SDL_Main --- Init\n");

  SDL_SetMainReady();
  
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    if ( DEBUG_MSGS ) { 
      char szMsg[256];
      sprintf(szMsg,
    "Couldn't initialize SDL: %s\n", 
         SDL_GetError()
      );
      vTraceMsg(szMsg);
    }
    return 1;
  }
  
  // Create a window
  window = SDL_CreateWindow(
    "SDLFW",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, 
    WINDOW_WIDTH, 
    WINDOW_HEIGHT, 
    SDL_WINDOW_SHOWN
  );

  // Create a renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

  SDL_RenderPresent(renderer);
 
  vInitRenderList(renderer, &SDL_RECT_Hud, SDL_RECT, SDL_RenderDrawRect, &SDL_RECT_Hud);
 
  SDL_Event event;
  while (gbRunning) {
    while ( SDL_PollEvent(&event) ){
      if (event.type == SDL_QUIT )
        gbRunning = FALSE;
        
      break;
    }
    ui64ElapsedTime = SDL_GetTicks64();
    
    SDL_SetRenderDrawColor(gstSDLRender.pSDL_Renderer, 255, 255, 255, 255); 
    SDL_RenderClear(renderer);
    
    vRenderObjectFromList(&SDL_RECT_Hud);
    // Update the screen
    SDL_RenderPresent(renderer);
    ui64ElapsedTime -= SDL_GetTicks64();
    if (ui64ElapsedTime <= 20) SDL_Delay(20 - ui64ElapsedTime);

  }
  
  // Don't forget to destroy the texture when you're done with it
  // SDL_DestroyTexture(pSDL_TXTR_Hud);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
