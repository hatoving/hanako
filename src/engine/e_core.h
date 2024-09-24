#ifndef E_CORE_H
#define E_CORE_H

#include "e_scene.h"

extern char* E_CORE_WINDOWTITLE;
extern E_Scene* E_CORE_CURRENTSCENE;

void E_Init();
void E_Close();

void E_HandleMiscInputs();

void E_SetScene(E_Scene* scene);
void E_UpdateCurrentScene();
void E_DrawCurrentScene();

void E_StartDrawing();
void E_EndDrawing();

#endif