#ifndef G_SETTINGS_H
#define G_SETTINGS_H

#include <stdbool.h>
#include "../engine/e_screen.h"

typedef struct {
	float music_volume;
	float sfx_volume;
	float ambience_volume;

	int current_render_mode;

	/*
		If we are on the pixel mode, then tell
		the game to render out a border (if the user
		wants it to.) <= 0 == No border.
	*/
	int current_border;

	bool billnear_filtering;
	bool fullscreen;
} G_Settings;

extern G_Settings* G_SETTINGS_CURRENT;

void G_Settings_Load();
void G_Settings_Save();
void G_Settings_Close();

G_Settings* G_Settings_CreateDefault();


#endif