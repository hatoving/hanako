#ifndef G_BUTTON_LABEL_H
#define G_BUTTON_LABEL_H

#include "g_button.h"
#include <raylib.h>

typedef struct {
	char* label;
	Font* font;
	int font_size;
	Color color;
} G_Button_LabelInfo;

typedef struct {
	G_Button* base;

	NPatchInfo patch_info;
	G_Button_LabelInfo label_info;

	float w, h, text_w, text_h;
} G_Button_Label;
G_Button_Label* G_Button_Label_Create(G_Button_LabelInfo label_info, G_ButtonFrameInfo info, Vector2 pos, Texture2D* texture);

void G_Button_Label_Update(G_Button_Label* button);
void G_Button_Label_Draw(G_Button_Label* button);
void G_Button_Label_Close(G_Button_Label* button);

#endif