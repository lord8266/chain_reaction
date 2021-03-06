#ifndef main_
#define main_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>

typedef struct pos pos;
typedef struct box box;
typedef struct layout layout;
typedef struct state state;
typedef struct explosion explosion;
typedef struct list list;
typedef struct node node;
typedef struct player player;
typedef struct animation animation;
typedef struct renderer renderer;
typedef struct base base;
typedef struct color color;
typedef struct textures textures;
typedef struct box_renderer box_renderer;
typedef struct stack stack;

// typedef void(*update_func)(int,int) ;
#include "list.h"
#include "core.h"
#include "render.h"
#endif