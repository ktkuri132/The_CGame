#ifndef __MENU_H__
#define __MENU_H__

#include "SDL3/SDL_stdinc.h"
#include <main.h>
#include <button.h>

typedef struct Menu Menu;

typedef struct{
    Uint16 x;
    Uint16 y;
    TTF_Font* font;
    const char* text;
    SDL_Color color;
} Menu_title;

typedef union{
    SDL_Color normal;
    struct {
        Uint8 r;
        Uint8 g;
        Uint8 b;
        Uint8 a;
    } components;
}Menu_Background_Color;

struct Menu{
    SDL_FRect rect;
    Menu_title title;
    Menu_Background_Color background_color;
    void (*update)(Menu* menu,SDL_Renderer *renderer);
    Button* buttons[];
};


Menu* menu_init(const char* title, float x, float y, float w, float h, TTF_Font* font,
				SDL_Color title_color, SDL_Color background_color);
int menu_deinit(Menu* menu);
int menu_register_button(Menu* menu, Button* button);
void menu_update(Menu* menu, SDL_Renderer *renderer);
void menu_handle_event(Menu* menu, SDL_Event* event);
#endif /* __MENU_H__ */ 