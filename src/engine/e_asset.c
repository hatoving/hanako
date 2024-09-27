#include "e_asset.h"
#include "../m_global.h"

#include <stdio.h>
#include <stdlib.h>

E_Asset* E_Asset_Create(char* label, char* asset_path, E_AssetType type, bool preload) {
    E_Asset* asset = (E_Asset*)malloc(sizeof(E_Asset));

    asset->info.label = label;
    asset->info.type = type;
    asset->info.path = asset_path;
    asset->info.preload = preload;

    asset->is_loaded = false;
    printf("E: Creating asset \"%s\" with type %i\n", asset->info.label, (int)asset->info.type);

    return asset;
}

void E_Asset_Load(E_Asset* asset) {
    switch (asset->info.type) {
        case E_ASSET_TYPE_SOUND: {
            Sound* snd = malloc(sizeof(Sound));
            if (snd != NULL) {
                *snd = LoadSound(TextFormat(asset->info.path, M_BASE_DATAPATH));
                asset->data = (void*)snd;
                asset->is_loaded = true;
            } else {
                printf("E: Memory allocation failed for sound asset \"%s\".", asset->info.label);
                asset->data = NULL;
                asset->is_loaded = false;
            }
            break;
        }
        case E_ASSET_TYPE_MUSIC: {
            Music* snd = malloc(sizeof(Music));
            if (snd != NULL) {
                *snd = LoadMusicStream(TextFormat(asset->info.path, M_BASE_DATAPATH));
                asset->data = (void*)snd;
                asset->is_loaded = true;
            } else {
                printf("E: Memory allocation failed for music asset \"%s\".", asset->info.label);
                asset->data = NULL;
                asset->is_loaded = false;
            }
            break;
        }
        case E_ASSET_TYPE_TEXTURE: {
            Texture2D* tex = malloc(sizeof(Texture2D));
            if (tex != NULL) {
                *tex = LoadTexture(TextFormat(asset->info.path, M_BASE_DATAPATH));
                asset->data = (void*)tex;
                asset->is_loaded = true;
            } else {
                printf("E: Memory allocation failed for texture asset \"%s\".", asset->info.label);
                asset->data = NULL;
                asset->is_loaded = false;
            }
            break;
        }
        case E_ASSET_TYPE_FONT: {
            Font* fnt = malloc(sizeof(Font));
            if (fnt != NULL) {
                *fnt = LoadFont(TextFormat(asset->info.path, M_BASE_DATAPATH));
                asset->data = (void*)fnt;
                asset->is_loaded = true;
            } else {
                printf("E: Memory allocation failed for font asset \"%s\".", asset->info.label);
                asset->data = NULL;
                asset->is_loaded = false;
            }
            break;
        }
        default: {
            printf("E: Invalid type for \"%s\" at \"%s\".", asset->info.label, asset->info.path);
            asset->data = NULL;
            asset->is_loaded = false;
            break;
        }
    }
}


void E_Asset_Close(E_Asset* asset) {
    if (asset == NULL && asset->data == NULL) return;
    
    switch (asset->info.type) {
        case E_ASSET_TYPE_SOUND: {
            if (asset->data != NULL)
                UnloadSound(*(Sound*)asset->data);
            break;
        }
        case E_ASSET_TYPE_MUSIC: {
            if (asset->data != NULL)
                UnloadMusicStream(*(Music*)asset->data);
            break;
        }
        case E_ASSET_TYPE_TEXTURE: {
            if (asset->data != NULL)
                UnloadTexture(*(Texture2D*)asset->data);
            break;
        }
        case E_ASSET_TYPE_FONT: {
            if (asset->data != NULL)
                UnloadFont(*(Font*)asset->data);
            break;
        }
    }

    asset->data = NULL;
    asset->is_loaded = false;
}