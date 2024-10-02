#include "g_desktop_icons.h"
#include "../../m_assets.h"

#include <stdio.h>
#include <stdlib.h>

const char* G_DESKTOP_ICONLABELS[] = {
	"cd"
};

void G_Desktop_Icons_Init() {
	int count = sizeof(G_DESKTOP_ICONLABELS) / sizeof(G_DESKTOP_ICONLABELS[0]);
	for (int i = 0; i < count; i++) {
		M_Assets_LoadAssetByLabel(TextFormat("desktop/gfx/icons/%s", G_DESKTOP_ICONLABELS[i]));
	}
}

Texture2D* G_Desktop_Icons_GetByLabel(char* label) {
	return (Texture2D*)M_Assets_GetAssetDataByLabel(TextFormat("desktop/gfx/icons/%s", label));
}

void G_Desktop_Icons_Close() {
	int count = sizeof(G_DESKTOP_ICONLABELS) / sizeof(G_DESKTOP_ICONLABELS[0]);
	for (int i = 0; i < count; i++) {
		M_Assets_CloseAssetByLabel(TextFormat("desktop/gfx/icons/%s", G_DESKTOP_ICONLABELS[i]));
	}
}
