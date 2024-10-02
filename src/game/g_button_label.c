#include "g_button_label.h"
#include "g_cursor.h"

#include "../m_assets.h"

#include <stdio.h>
#include <stdlib.h>

void G_Button_Label_CalcPosSize(G_Button_Label* button) {
	Vector2 text_size = MeasureTextEx(
		*button->label_info.font,
		button->label_info.label,
		button->label_info.font_size,
		0.0f
	);
	button->text_w = text_size.x;
	button->text_h = text_size.y;
	
	button->w = text_size.x + 20.0f;
	button->h = text_size.y + 10.0f;
}
 
G_Button_Label* G_Button_Label_Create(G_Button_LabelInfo label_info, G_ButtonFrameInfo info, Vector2 pos, Texture2D* texture) {
	G_Button_Label* button = (G_Button_Label*)malloc(sizeof(G_Button_Label));
	button->base = G_Button_Create(
		info, pos, texture
	);

	button->label_info = label_info;
	button->patch_info = (NPatchInfo){
		(Rectangle){
			0.0f, 0.0f, 11.0f, 11.0f
		},
		4, 4, 4, 4, NPATCH_NINE_PATCH
	};

	G_Button_Label_CalcPosSize(button);
	return button;
}

void G_Button_Label_Update(G_Button_Label* button) {
	Vector2 mouse_position = (Vector2){G_CURSOR_X, G_CURSOR_Y};

	G_Button_Label_CalcPosSize(button);
	Rectangle rec = (Rectangle){
		button->base->pos.x,
		button->base->pos.y,
		button->w,
		button->h
	};

	if (CheckCollisionPointRec(mouse_position, rec)) {
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			button->base->clicked = true;
		} else {
			button->base->hovering = true;
		}

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && button->base->clicked) {
			button->base->clicked = false;
			button->base->hovering = false;

			if (button->base->click_callback != NULL) {
				button->base->click_callback(button->base->click_callback_data);
			}
		}
	} else {
		button->base->clicked = false;
		button->base->hovering = false;
	}
}

void G_Button_Label_Draw(G_Button_Label* button) {
	int frame = 0;

	if (button->base->hovering) frame = button->base->frame_info.hover_frame;
	else frame = button->base->frame_info.idle_frame;
	if (button->base->clicked) frame = button->base->frame_info.press_frame;
	else frame = button->base->frame_info.idle_frame;

	button->patch_info.source = (Rectangle){
		button->base->frame_info.frame_size.x * (float)frame,
		button->base->frame_info.frame_size.y * (float)frame,
		button->base->frame_info.frame_size.x,
		button->base->frame_info.frame_size.y
	};
	DrawTextureNPatch(
		*button->base->texture, 
		button->patch_info,
		(Rectangle){
			(float)button->base->pos.x,
			(float)button->base->pos.y,
			button->w,
			button->h
		},
		(Vector2){0.0f, 0.0f}, 
		0.0f, 
		WHITE
	);

	Vector2 text_pos = {
		button->base->pos.x + (button->w - button->text_w) / 2.0f,
		button->base->pos.y + (button->h - button->text_h) / 2.0f + 1
	};

	DrawTextEx(
		*button->label_info.font,
		button->label_info.label,
		text_pos,
		button->label_info.font_size,
		0.0f, 
		button->label_info.color
	);
}

void G_Button_Label_Close(G_Button_Label* button) {
	G_Button_Close(button->base);
	free(button);
}