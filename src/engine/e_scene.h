#ifndef E_SCENE_H
#define E_SCENE_H

#include <stdbool.h>

typedef struct {
    void (*init)();
    void (*update)();
    void (*draw)();
    void (*close)();

    char* label;
} E_Scene;
E_Scene* E_Scene_Create(const char* lable, void* init_function, void* update_function, void* draw_function, void* close_function);

#endif