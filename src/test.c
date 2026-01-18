#include <test.h>

void game_test(SDL_Renderer *renderer, bool *running,SDL_Event* event,const bool* keyboardState, Mouse_State* mouse_state) {
    printf("Game test function called.\n");
    SDL_FRect rect = {
    .x = 350, // X坐标
    .y = 250, // Y坐标
    .w = 100, // 宽度
    .h = 100  // 高度
	};
    while (*running) {
		SDL_Windows_ESC_Event_Check(running, *event);
		SDL_SetRenderDrawColor(renderer, 50, 100, 150, 255); // 蓝灰色背景
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // 白色

        keyboardState = SDL_GetKeyboardState(NULL);
        if (keyboardState[SDL_SCANCODE_W]) {
            printf("W键被按下\n");
            rect.y -= MOVE_SPEED_Y; // 向上移动矩形
        } else if (keyboardState[SDL_SCANCODE_S]) {
            printf("S键被按下\n");
            rect.y += MOVE_SPEED_Y; // 向下移动矩形
        } else if (keyboardState[SDL_SCANCODE_A]) {
            printf("A键被按下\n");
            rect.x -= MOVE_SPEED_X; // 向左移动矩形
        } else if (keyboardState[SDL_SCANCODE_D]) {
            printf("D键被按下\n");
            rect.x += MOVE_SPEED_X; // 向右移动矩形
        }
        SDL_GetMouseState(&mouse_state->x, &mouse_state->y);
        printf("鼠标位置: (%.1f, %.1f)\n", mouse_state->x, mouse_state->y);
        SDL_RenderFillRect(renderer, &rect);

		// ----------------------------------------
		// 4.4 显示渲染结果（类似于LCD刷新）
		// ----------------------------------------
		SDL_RenderPresent(renderer);

		// ----------------------------------------
		// 4.5 简单的帧率控制（约60FPS）
		// ----------------------------------------
		SDL_Delay(10); // 延时10毫秒
	}
    
}