/**
 * rect.h
 *
 * Written by Renato Fermi <repiazza@gmail.com> in March 2024
 *
 * Rect handling
 *
 */
#include <consts.h>
#include <board.h>
#ifndef _RECT_H_
  #define _RECT_H_

  
  typedef struct STRUCT_RECT_VALUES {
      double dFactor;    // Angular coefficient
      double dAddAmount;
  } STRUCT_RECT_VALUES, *PSTRUCT_RECT_VALUES;

  typedef struct STRUCT_RECT_DIMENSIONS{
    STRUCT_RECT_VALUES stX;
    STRUCT_RECT_VALUES stY;
    STRUCT_RECT_VALUES stW;
    STRUCT_RECT_VALUES stH;
  } STRUCT_RECT_DIMENSIONS, PSTRUCT_RECT_DIMENSIONS;

  extern STRUCT_RECT_DIMENSIONS gstButtonHUD_Dimension;
  extern STRUCT_RECT_DIMENSIONS gstCmdHUD_Dimensions;
  extern STRUCT_RECT_DIMENSIONS gstTmpHUD_Dimensions;
  
  /**
   * Set 
  */
  int iRECT_SetDimensions( SDL_Rect *pSDL_Rect, STRUCT_RECT_DIMENSIONS *pst_RECT_Dimensions ){
    if ( pSDL_Rect == NULL )
      return FALSE;

    pSDL_Rect->x = pst_RECT_Dimensions->stX.dFactor + pst_RECT_Dimensions->stX.dAddAmount;
    pSDL_Rect->y = pst_RECT_Dimensions->stY.dFactor + pst_RECT_Dimensions->stY.dAddAmount;
    pSDL_Rect->w = pst_RECT_Dimensions->stW.dFactor + pst_RECT_Dimensions->stW.dAddAmount;
    pSDL_Rect->h = pst_RECT_Dimensions->stH.dFactor + pst_RECT_Dimensions->stH.dAddAmount;
    return TRUE;
  }
  
  void vRECT_InitGlobalDimensions(void){
    (&gstTmpHUD_Dimensions)->stX.dFactor    = 0.06 * atoi( gstCmdLine.szWinWidth );
    (&gstTmpHUD_Dimensions)->stX.dAddAmount = -10;
    (&gstTmpHUD_Dimensions)->stY.dFactor    = 0.04 * atoi( gstCmdLine.szWinHeight );
    (&gstTmpHUD_Dimensions)->stY.dAddAmount = -( 20 + COL_RATIO );
    (&gstTmpHUD_Dimensions)->stW.dFactor    = atoi( gstCmdLine.szWinWidth ) / 2;
    (&gstTmpHUD_Dimensions)->stW.dAddAmount = -20;
    (&gstTmpHUD_Dimensions)->stH.dFactor    = COL_RATIO;
    (&gstTmpHUD_Dimensions)->stH.dAddAmount = -10;

    (&gstCmdHUD_Dimensions)->stX.dFactor    = atoi( gstCmdLine.szWinWidth ) / 4;
    (&gstCmdHUD_Dimensions)->stX.dAddAmount = 0;
    (&gstCmdHUD_Dimensions)->stY.dFactor    = 0;
    (&gstCmdHUD_Dimensions)->stY.dAddAmount = 0;
    (&gstCmdHUD_Dimensions)->stW.dFactor    = atoi( gstCmdLine.szWinWidth ) / 2;
    (&gstCmdHUD_Dimensions)->stW.dAddAmount = 0;
    (&gstCmdHUD_Dimensions)->stH.dFactor    = COL_RATIO;
    (&gstCmdHUD_Dimensions)->stH.dAddAmount = 0;

    (&gstButtonHUD_Dimension)->stX.dFactor    = 0.06 * atoi( gstCmdLine.szWinWidth );
    (&gstButtonHUD_Dimension)->stX.dAddAmount = -10;
    (&gstButtonHUD_Dimension)->stY.dFactor    = 0.04 * atoi( gstCmdLine.szWinHeight );
    (&gstButtonHUD_Dimension)->stY.dAddAmount = -30;
    (&gstButtonHUD_Dimension)->stW.dFactor    = atoi( gstCmdLine.szWinWidth ) / 2;
    (&gstButtonHUD_Dimension)->stW.dAddAmount = -20;
    (&gstButtonHUD_Dimension)->stH.dFactor    = COL_RATIO;
    (&gstButtonHUD_Dimension)->stH.dAddAmount = -10;
  }


    // Definições de proporções como percentuais da tela
  #define HUD_X_FACTOR 0.06  // Porcentagem da largura da tela
  #define HUD_Y_FACTOR 0.04  // Porcentagem da altura da tela
  #define HUD_WIDTH_FACTOR 0.5  // 50% da largura da tela
  #define HUD_HEIGHT_FACTOR 0.05  // 5% da altura da tela

  void vCalculateHUDRect(SDL_Rect *rect, double xFactor, double yFactor, double widthFactor, double heightFactor) {
    if (!rect) return;

    int screenWidth = atoi(gstCmdLine.szWinWidth);
    int screenHeight = atoi(gstCmdLine.szWinHeight);

    rect->x = (int)(xFactor * screenWidth);
    rect->y = (int)(yFactor * screenHeight);
    rect->w = (int)(widthFactor * screenWidth);
    rect->h = (int)(heightFactor * screenHeight);
  }

  void vInitializeAllHUDRects() {
    SDL_Rect tmpHudRect, cmdHudRect, buttonHudRect;

    vCalculateHUDRect(&tmpHudRect, HUD_X_FACTOR, HUD_Y_FACTOR, HUD_WIDTH_FACTOR, HUD_HEIGHT_FACTOR);
    vCalculateHUDRect(&cmdHudRect, HUD_X_FACTOR, HUD_Y_FACTOR, HUD_WIDTH_FACTOR, HUD_HEIGHT_FACTOR);
    vCalculateHUDRect(&buttonHudRect, HUD_X_FACTOR, HUD_Y_FACTOR, HUD_WIDTH_FACTOR, HUD_HEIGHT_FACTOR);

  }


#endif