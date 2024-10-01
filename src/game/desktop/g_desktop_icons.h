#ifndef G_DESKTOP_ICONS_H
#define G_DESKTOP_ICONS_H

#include <raylib.h>

void G_Desktop_Icons_Init();
Texture2D* G_Desktop_Icons_GetByLabel(char* label);
void G_Desktop_Icons_Close();

#endif