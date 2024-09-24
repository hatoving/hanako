#ifndef M_ASSET_H
#define M_ASSET_H

#include "engine/e_asset.h"

void M_Assets_Init();

E_Asset* M_Assets_GetAssetByLabel(char* label);
void* M_Assets_GetAssetDataByLabel(char* label);

void M_Assets_LoadAssetByLabel(char* label);
void M_Assets_CloseAssetByLabel(char* label);

void M_Assets_Close();

#endif