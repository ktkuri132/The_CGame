#ifndef __MAIN_H__
#define __MAIN_H__

#include "SDL3/SDL_mouse.h"
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <windows.h>

// 窗口尺寸（就像你定义LCD分辨率一样）
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define MOVE_SPEED_X 5.0f
#define MOVE_SPEED_Y 5.0f

typedef struct {
	float x;
	float y;
} Mouse_State;

void SDL_Windows_ESC_Event_Check(bool *running, SDL_Event event);
SDL_Window* Game_Init();

#endif /* __MAIN_H__ */

