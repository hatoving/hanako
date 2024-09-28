#include "m_scenes.h"

#include <stdlib.h>
#include <stdio.h>

#include "scenes/s_test.h"
#include "scenes/s_boot.h"
#include "scenes/s_desktop.h"

E_Scene* S_TEST = NULL;
E_Scene* S_BOOT = NULL;
E_Scene* S_DESKTOP = NULL;

void M_Scenes_Populate() {
	S_TEST = E_Scene_Create("__hanako_scene_Test", S_TestInit, S_TestUpdate, S_TestDraw, S_TestClose);
	S_BOOT = E_Scene_Create("__hanako_scene_Boot", S_BootInit, S_BootUpdate, S_BootDraw, S_BootClose);
	S_DESKTOP = E_Scene_Create("__hanako_scene_Desktop", S_DesktopInit, S_DesktopUpdate, S_DesktopDraw, S_DesktopClose);
}

void M_Scenes_Close() {
	free(S_TEST);
	free(S_BOOT);
	free(S_DESKTOP);
}