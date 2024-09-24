#include "g_scenes.h"

#include <stdlib.h>
#include <stdio.h>

#include "scenes/g_scene_test.h"
#include "scenes/g_scene_boot.h"

E_Scene* G_SCENE_TEST = NULL;
E_Scene* G_SCENE_BOOT = NULL;

void G_Scenes_Populate() {
    G_SCENE_TEST = E_Scene_Create("__hanako_scene_Test", G_Scene_TestInit, G_Scene_TestUpdate, G_Scene_TestDraw, G_Scene_TestClose);
    G_SCENE_BOOT = E_Scene_Create("__hanako_scene_Boot", G_Scene_BootInit, G_Scene_BootUpdate, G_Scene_BootDraw, G_Scene_BootClose);
}

void G_Scenes_Close() {
    free(G_SCENE_TEST);
    free(G_SCENE_BOOT);
}