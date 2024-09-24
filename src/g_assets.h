#ifndef G_ASSET_H
#define G_ASSET_H

#include "engine/e_asset.h"

void G_InitializeAssets();

E_Asset* G_GetAssetByLabel(char* label);
void* G_GetAssetDataByLabel(char* label);

void G_LoadAssetByLabel(char* label);
void G_CloseAssetByLabel(char* label);

void G_CloseAssets();

#endif