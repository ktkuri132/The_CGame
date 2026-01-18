#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <main.h>
#include <text.h>

typedef struct Button Button;

typedef union {
    SDL_Color normal;
    struct {
        Uint8 r;
        Uint8 g;
        Uint8 b;
        Uint8 a;
    } components;
}Button_Color;

typedef struct{
    float x;
    float y;
    TTF_Font* font;
    const char* text;
    SDL_Color color;
} Button_font;

typedef struct{
    void **argv;
} Button_Args;

struct Button {
    SDL_FRect rect;
    bool is_pressed;
    Button_Color colors;
    Button_font text;
    Button_Args on_click_args;
    Button_Args on_release_args;
    int (*on_click)(void **argv);
    int (*on_release)(void **argv);
    void (*update)(Button* button,SDL_Renderer *renderer);
};

Button* button_init(float x, float y, float w, float h, Button_Color colors, int (*on_click)(void **argv), int (*on_release)(void **argv));
Button* button_init_with_font(float x, float y, float w, float h,Button_Color colors, int (*on_click)(void **argv), int (*on_release)(void **argv), 
                                TTF_Font* font, const char* text, SDL_Color color);
int button_deinit(Button* button);
void button_handle_event(Button* button, SDL_Event* event);
void button_update(Button* button, SDL_Renderer *renderer);
void button_update_with_text(Button* button, SDL_Renderer *renderer);
#endif /* __BUTTON_H__ */