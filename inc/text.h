#ifndef __TEXT_H__
#define __TEXT_H__

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_render.h>
#include <stdbool.h>
#include <stdio.h>

bool initialize_ttf();
void shutdown_ttf();
TTF_Font* load_font(const char* font_path, int font_size);
void close_font(TTF_Font* font);
void Text_Draw(SDL_Renderer* renderer, TTF_Font* font, const char* text
                , SDL_Color color, float x, float y);


#endif /* __TEXT_H__ */