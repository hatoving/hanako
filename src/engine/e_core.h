#ifndef E_CORE_H
#define E_CORE_H

#include "e_scene.h"

extern char* E_CORE_WINDOWTITLE;
extern E_Scene* E_CORE_CURRENTSCENE;

void E_Core_Init();
void E_Core_Close();

void E_Core_HandleMiscInputs();

void E_Core_SetScene(E_Scene* scene);
void E_Core_UpdateCurrentScene();
void E_Core_DrawCurrentScene();

void E_Core_StartDrawing();
void E_Core_EndDrawing();

#endif