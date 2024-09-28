#ifndef G_SETTINGS_H
#define G_SETTINGS_H

#include <stdbool.h>
#include <stdint.h>

#include "../engine/e_screen.h"

typedef struct {
	float music_volume;
	float sfx_volume;
	float ambience_volume;

	uint8_t current_render_mode;

	/*
		If we are on the pixel mode, then tell
		the game to render out a border (if the user
		wants it to.) <= 0 == No border.
	*/
	uint8_t current_border;
	uint8_t billnear_filtering;
	uint8_t fullscreen;

	uint8_t last_save_slot_used;
} G_Settings;
extern G_Settings* G_SETTINGS_CURRENT;

void G_Settings_Load();
void G_Settings_Save();
void G_Settings_Close();

G_Settings* G_Settings_CreateDefault();


#endif