#ifndef G_BUTTON_H
#define G_BUTTON_H

#include <raylib.h>

typedef struct {
	int idle_frame, hover_frame, press_frame;
	Vector2 frame_size;
	int frame_count;
} G_ButtonFrameInfo;

typedef struct {
	G_ButtonFrameInfo frame_info;

	Texture2D* texture;
	char* texture_label;

	Vector2 pos;

	bool clicked;
	bool hovering;

	void (*click_callback)(void* data);
	void* click_callback_data;
} G_Button;
G_Button* G_Button_Create(G_ButtonFrameInfo info, Vector2 pos, Texture2D* texture);

void G_Button_Update(G_Button* button);
void G_Button_Draw(G_Button* button);
void G_Button_Close(G_Button* button);

#endif