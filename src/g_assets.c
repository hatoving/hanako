#include "g_assets.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

E_AssetDescriptor asset_info_table[] = {
    /* preload assets */
    { "preload/gfx/cursor", "data/preload/graphics/cursor.png", E_ASSET_TYPE_TEXTURE, true },
    { "preload/snd/beep", "data/preload/sounds/computer_beep.ogg", E_ASSET_TYPE_SOUND, true },
    { "preload/fnt/system", "data/preload/fonts/system.ttf", E_ASSET_TYPE_FONT, true },

    /* boot sequence */
    { "boot/gfx/trophy", "data/main/boot/graphics/trophy.png", E_ASSET_TYPE_TEXTURE, false },
};

E_Asset** assets = NULL;
int asset_count = 0;

void G_InitializeAssets() {
    int asset_info_count = sizeof(asset_info_table) / sizeof(asset_info_table[0]);
    assets = (E_Asset**)malloc(asset_info_count * sizeof(E_Asset*));

    for (int i = 0; i < asset_info_count; i++) {
        assets[i] = E_Asset_Create(asset_info_table[i].label, asset_info_table[i].path, asset_info_table[i].type, asset_info_table[i].preload);
        if (assets[i]->info.preload) {
            E_Asset_Load(assets[i]);
        } else {
            assets[i]->is_loaded = false;
        }
        asset_count++;
    }
    printf("E: Total asset count -- %i\n", asset_count);
}

E_Asset* G_GetAssetByLabel(char* label) {
    if (label != NULL && strlen(label) > 0) {
        for (int i = 0; i < asset_count; i++) {
            if (assets[i] != NULL && strcmp(assets[i]->info.label, label) == 0) {
                return assets[i];
            }
        }
    }
    return NULL;
}

void* G_GetAssetDataByLabel(char* label) {
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

void G_CloseAssets() {
    for (int i = 0; i < asset_count; i++) {
        if (assets[i] != NULL) {
            if (assets[i]->is_loaded) {
                E_Asset_Close(assets[i]);
            }
            free(assets[i]);
            assets[i] = NULL;
        }
    }
    free(assets);
    assets = NULL;
}