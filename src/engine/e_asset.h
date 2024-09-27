#ifndef E_ASSET_H
#define E_ASSET_H

#include <raylib.h>

typedef enum {
    E_ASSET_TYPE_SOUND, // Returns a raylib Sound struct
    E_ASSET_TYPE_MUSIC, // Returns a raylib Music struct
    E_ASSET_TYPE_FONT, // Retuns a raylib Font struct
    E_ASSET_TYPE_TEXTURE // Retuns a raylib Texture2D struct
} E_AssetType;

typedef struct {
    char* label;
    char* path;
    E_AssetType type;
    bool preload;
} E_AssetDescriptor;

typedef struct {
    bool is_loaded;
    E_AssetDescriptor info;
    void* data;
} E_Asset;
E_Asset* E_Asset_Create(char* label, char* asset_path, E_AssetType type, bool preload);

void E_Asset_Load(E_Asset* asset);
void E_Asset_Close(E_Asset* asset);

#endif