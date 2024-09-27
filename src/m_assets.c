#include "m_assets.h"
#include "m_global.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


E_AssetDescriptor asset_info_table[] = {
	/* preload assets */
	{ "preload/gfx/cursor", "%s/preload/graphics/cursor.png", E_ASSET_TYPE_TEXTURE, true },

	{ "preload/snd/beep", "%s/preload/sounds/computer_beep.ogg", E_ASSET_TYPE_SOUND, true },
	{ "preload/snd/power_button", "%s/preload/sounds/computer_power_button.ogg", E_ASSET_TYPE_SOUND, true },

	{ "preload/mus/ambience", "%s/preload/music/computer_ambience.ogg", E_ASSET_TYPE_MUSIC, true },
	{ "preload/mus/hdd", "%s/preload/music/computer_hdd.ogg", E_ASSET_TYPE_MUSIC, true },

	{ "preload/snd/mouse_click", "%s/preload/sounds/mouse_click.ogg", E_ASSET_TYPE_SOUND, true },
	{ "preload/snd/keyboard_click", "%s/preload/sounds/keyboard_click.ogg", E_ASSET_TYPE_SOUND, true },

	{ "preload/fnt/system", "%s/preload/fonts/system.ttf", E_ASSET_TYPE_FONT, true },

		/* preload assets ~~ borders */
	{ "preload/gfx/borders/1", "%s/preload/graphics/borders/simple.png", E_ASSET_TYPE_TEXTURE, true },

	/* boot sequence */
	{ "boot/gfx/hat_logo", "%s/boot/graphics/hatoving.png", E_ASSET_TYPE_TEXTURE, false },
	{ "boot/gfx/trophy", "%s/boot/graphics/trophy.png", E_ASSET_TYPE_TEXTURE, false },
	{ "boot/gfx/starlight_bg", "%s/boot/graphics/loading.png", E_ASSET_TYPE_TEXTURE, false },
	{ "boot/gfx/starlight_loadbar", "%s/boot/graphics/loading_bar.png", E_ASSET_TYPE_TEXTURE, false },
};

E_Asset** assets = NULL;
int asset_count = 0;

void M_Assets_Init() {
	printf("\n/// ~~ INITIALIZING ASSETS ~~ ///\n");

	int asset_info_count = sizeof(asset_info_table) / sizeof(asset_info_table[0]);
	assets = (E_Asset**)malloc(asset_info_count * sizeof(E_Asset*));

	for (int i = 0; i < asset_info_count; i++) {
		assets[i] = E_Asset_Create(asset_info_table[i].label, asset_info_table[i].path, asset_info_table[i].type, asset_info_table[i].preload);
		if (assets[i]->info.preload) {
			E_Asset_Load(assets[i]);
		}
		asset_count++;
	}
	printf("/// ~~ DONE INITIALIZING ASSETS ///\nE: TOTAL ASSET COUNT -- %i\n\n", asset_count);
}

E_Asset* M_Assets_GetAssetByLabel(char* label) {
	if (label != NULL && strlen(label) > 0) {
		for (int i = 0; i < asset_count; i++) {
			if (assets[i] != NULL && strcmp(assets[i]->info.label, label) == 0) {
				return assets[i];
			}
		}
	}
	return NULL;
}

void* M_Assets_GetAssetDataByLabel(char* label) {
	if (label != NULL && strlen(label) > 0) {
		for (int i = 0; i < asset_count; i++) {
			if (assets[i] != NULL && strcmp(assets[i]->info.label, label) == 0) {
				if (assets[i]->data != NULL) {
					return assets[i]->data;
				}
			}
		}
	}
	return NULL;
}

void M_Assets_LoadAssetByLabel(char* label) {
	if (label != NULL && strlen(label) > 0) {
		for (int i = 0; i < asset_count; i++) {
			if (assets[i] != NULL && !assets[i]->is_loaded && strcmp(assets[i]->info.label, label) == 0) {
				E_Asset_Load(assets[i]);
			}
		}
	}
}
void M_Assets_CloseAssetByLabel(char* label) {
	if (label != NULL && strlen(label) > 0) {
		for (int i = 0; i < asset_count; i++) {
			if (assets[i] != NULL && assets[i]->is_loaded && strcmp(assets[i]->info.label, label) == 0) {
				E_Asset_Close(assets[i]);
			}
		}
	}
}

void M_Assets_Close() {
	if (assets == NULL || asset_count == 0) {
		return;
	}
	
	for (int i = 0; i < asset_count; i++) {
		if (assets[i] != NULL) {
			if (assets[i]->is_loaded) {
				E_Asset_Close(assets[i]);
				assets[i]->is_loaded = false;
			}
			free(assets[i]);
			assets[i] = NULL;
		}
	}
	free(assets);
	assets = NULL;

	asset_count = 0;
}