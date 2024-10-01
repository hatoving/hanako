#include "g_button.h"
#include "g_cursor.h"

#include "../m_assets.h"

#include <stdio.h>
#include <stdlib.h>

G_Button* G_Button_Create(G_ButtonFrameInfo info, Vector2 pos, Vector2 pivot, Texture2D* texture) {
	G_Button* button = (G_Button*)malloc(sizeof(G_Button));

	button->frame_info = info;
	button->pos = pos;
	button->pivot = pivot;

	button->texture = texture;
	return button;
}

void G_Button_Update(G_Button* button) {
	Vector2 mouse_position = (Vector2){G_CURSOR_X, G_CURSOR_Y};

	Rectangle rec = (Rectangle){
		button->pos.x,
		button->pos.y,
		button->frame_info.frame_size.x,
		button->frame_info.frame_size.y
	};

	if (CheckCollisionPointRec(mouse_position, rec)) {
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			button->clicked = true;
		} else {
			button->hovering = true;
		}

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && button->clicked) {
			button->clicked = false;
			button->hovering = false;

			if (button->click_callback != NULL) {
				button->click_callback(button->click_callback_data);
			}
		}
	} else {
		button->clicked = false;
	}
}

void G_Button_Draw(G_Button* button) {
	int frame = 0;

	if (button->hovering) frame = button->frame_info.hover_frame;
	else if (button->clicked) frame = button->frame_info.press_frame;
	else frame = button->frame_info.idle_frame;

	DrawTextureRec(
		*button->texture,
		(Rectangle){
			button->frame_info.frame_size.x * frame,
			button->frame_info.frame_size.y * frame,
			button->frame_info.frame_size.x,
			button->frame_info.frame_size.y
		},
		(Vector2){
			button->pos.x,
			button->pos.y,
		},
		WHITE
	);
}

void G_Button_Close(G_Button* button) {
	free(button);
}