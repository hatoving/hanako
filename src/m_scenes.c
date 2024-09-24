#include "m_scenes.h"

#include <stdlib.h>
#include <stdio.h>

#include "scenes/s_test.h"
#include "scenes/s_boot.h"

E_Scene* S_TEST = NULL;
E_Scene* S_BOOT = NULL;

void M_Scenes_Populate() {
    S_TEST = E_Scene_Create("__hanako_scene_Test", S_TestInit, S_TestUpdate, S_TestDraw, S_TestClose);
    S_BOOT = E_Scene_Create("__hanako_scene_Boot", S_BootInit, S_BootUpdate, S_BootDraw, S_BootClose);
}

void M_Scenes_Close() {
    free(S_TEST);
    free(S_BOOT);
}