#include "g_desktop_icons.h"
#include "../../m_assets.h"

#include <stdio.h>
#include <stdlib.h>

const char* G_DESKTOP_LABELS[] = {
	"desktop/gfx/window",
	"desktop/gfx/bgs/0",
	"desktop/gfx/window/buttons/generic",
	"desktop/gfx/window/buttons/close"
};

void G_Desktop_Assets_Init() {
	int count = sizeof(G_DESKTOP_LABELS) / sizeof(G_DESKTOP_LABELS[0]);
	for (int i = 0; i < count; i++) {
		M_Assets_LoadAssetByLabel(G_DESKTOP_LABELS[i]);
	}
}

void G_Desktop_Assets_Close() {
	int count = sizeof(G_DESKTOP_LABELS) / sizeof(G_DESKTOP_LABELS[0]);
	for (int i = 0; i < count; i++) {
		M_Assets_CloseAssetByLabel(G_DESKTOP_LABELS[i]);
	}
}
