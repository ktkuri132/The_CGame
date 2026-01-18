#ifndef PLOT_H
#define PLOT_H
#include "main.h"
#include <text.h>
typedef struct {
    float* x_data;
    float* y_data;
    int data_count;
}Plot_Data;

typedef struct{
    float x;
    float y;
    TTF_Font* font;
    const char* text;
    SDL_Color color;
} Plot_font;

struct Plot{
    SDL_FRect rect;
    Plot_font title;
};

#endif /* PLOT_H */