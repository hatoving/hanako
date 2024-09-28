#include "g_settings.h"
#include "../m_global.h"

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

G_Settings* G_SETTINGS_CURRENT = NULL;

void G_Settings_Save() {
    char* path = TextFormat("%s/settings.dat", M_BASE_SAVEPATH);

    FILE* settings_file = fopen(path, "wb");
    if (settings_file != NULL) {
        fwrite(G_SETTINGS_CURRENT, sizeof(G_Settings), 1, settings_file);
        fclose(settings_file);
    } else {
        printf("G: Failed to open settings file for writing at \"%s\".\n", path);
    }
}

void G_Settings_Load() {
	char* path = TextFormat("%s/settings.dat", M_BASE_SAVEPATH);
	FILE* settings_file = fopen(path, "rb");

	if (settings_file != NULL) {
		printf("G: Found settings file at \"%s\". Reading...\n", path);

		G_SETTINGS_CURRENT = (G_Settings*)malloc(sizeof(G_Settings));
		if (fread(G_SETTINGS_CURRENT, sizeof(G_Settings), 1, settings_file) != 1) {
			printf("G: Error - Failed to read settings from file.\n");
			fclose(settings_file);

			free(G_SETTINGS_CURRENT);
			G_SETTINGS_CURRENT = G_Settings_CreateDefault();
			G_Settings_Save();

			return;
		}
		fclose(settings_file);
	} else {
		printf("G: No settings file found. Creating default...\n", path);

		G_SETTINGS_CURRENT = G_Settings_CreateDefault();
		G_Settings_Save();
	}
}

G_Settings* G_Settings_CreateDefault() {
	G_Settings* settings = (G_Settings*)malloc(sizeof(G_Settings));

	settings->music_volume = 1.0f;
	settings->sfx_volume = 1.0f;
	settings->ambience_volume = 1.0f;

	settings->current_render_mode = (int)E_SCREEN_RM_PIXEL;
	settings->current_border = 1;

	settings->billnear_filtering = false;
	settings->fullscreen = false;

	settings->last_save_slot_used = 0;
	return settings;
}

void G_Settings_Close() {
	free(G_SETTINGS_CURRENT);
}