#include "g_state.h"
#include "../m_global.h"

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

G_State* G_STATE_CURRENT = NULL;

void G_State_Load(uint8_t slot) {
	char* path = TextFormat("%s/save_%i.dat", M_BASE_SAVEPATH, slot);
	FILE* save_file = fopen(path, "rb");

	if (save_file != NULL) {
		printf("G: Found save file (slot %i) at \"%s\". Reading...\n", slot, path);

		G_STATE_CURRENT = (G_State*)malloc(sizeof(G_State));
		if (fread(G_STATE_CURRENT, sizeof(G_State), 1, save_file) != 1) {
			printf("G: Error - Failed to read save file (slot %i) from file.\n", slot);
			fclose(save_file);

			free(G_STATE_CURRENT);
			G_STATE_CURRENT = G_State_CreateDefault();
			G_State_Save(slot);
			
			return;
		}
		fclose(save_file);
	} else {
		printf("G: No save file (slot %i) found. Creating default...\n", slot);

		G_STATE_CURRENT = G_State_CreateDefault();
		G_State_Save(slot);
	}
}
void G_State_Save(uint8_t slot) {
	char* path = TextFormat("%s/save_%i.dat", M_BASE_SAVEPATH, slot);

    FILE* save_file = fopen(path, "wb");
    if (save_file != NULL) {
        fwrite(G_STATE_CURRENT, sizeof(G_State), 1, save_file);
        fclose(save_file);
    } else {
        printf("G: Failed to open save file (slot %i) for writing at \"%s\".\n", slot, path);
    }
}

G_State* G_State_CreateDefault() {
	G_State* state = (G_State*)malloc(sizeof(G_State));

	state->first_time = 1;
	state->time_played = 0.0f;

	return state;
}