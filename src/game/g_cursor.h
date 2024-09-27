#ifndef G_CURSOR_H
#define G_CURSOR_H

extern float G_CURSOR_X;
extern float G_CURSOR_Y;

void G_Cursor_Init();
void G_Cursor_Update();
void G_Cursor_Draw();

void G_Cursor_ToggleVisibility();
void G_Cursor_SetVisibility(bool value);

void G_Cursor_Close();

#endif