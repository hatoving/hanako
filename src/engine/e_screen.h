#ifndef E_SCREEN_H
#define E_SCREEN_H

#include <raylib.h>

/*
	Available Render Modes
*/
typedef enum {
	E_SCREEN_RM_FIT,
	E_SCREEN_RM_PIXEL,
	E_SCREEN_RM_STRETCH,
	E_SCREEN_RM_COUNT
} E_SCREEN_RM;

extern E_SCREEN_RM E_SCREEN_CURRENT_RM;
extern RenderTexture2D E_SCREEN_TEX;

extern bool E_SCREEN_FULLSCREEN;

/*
	Gets set by the engine to be used
	for getting shit that's outside of
	the actual render area, like the mouse
	poistion
*/
extern float E_SCREEN_SCALE_X;
extern float E_SCREEN_SCALE_Y;

void E_HandleScreen();
void E_SetFullscreen(bool on);

#endif