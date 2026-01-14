/**
 * 我的第一个SDL3程序
 *
 * 这个程序会创建一个窗口，就像嵌入式开发中初始化LCD屏幕一样
 */

#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <windows.h>

// 窗口尺寸（就像你定义LCD分辨率一样）
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define MOVE_SPEED_X 5.0f
#define MOVE_SPEED_Y 5.0f

SDL_Window* Game_Init() {
	SetConsoleOutputCP(65001);
	// ========================================
	// 第1步：初始化SDL
	// 这就像嵌入式中的外设初始化
	// ========================================
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		// SDL_GetError() 类似于获取错误码
		printf("SDL初始化失败: %s\n", SDL_GetError());
		return NULL;
	}
	printf("SDL3 初始化成功!\n");
	static SDL_Window* window;
	// ========================================
	// 第2步：创建窗口
	// 这就像初始化LCD显示屏
	// ========================================
	window = SDL_CreateWindow("我的第一个游戏", // 窗口标题
							  WINDOW_WIDTH,		// 宽度
							  WINDOW_HEIGHT,	// 高度
							  0					// 窗口标志（0表示默认）
	);

	if (window == NULL) {
		printf("创建窗口失败: %s\n", SDL_GetError());
		SDL_Quit();
		return NULL;
	}
	printf("窗口创建成功!\n");
	return window;
}


void SDL_Windows_ESC_Event_Check(bool *running) {
	SDL_Event event; // 事件结构体，用于接收用户输入
	while (SDL_PollEvent(&event)) {
		// 检查事件类型
		switch (event.type) {
			case SDL_EVENT_QUIT:
				// 用户点击了关闭按钮
				printf("收到退出事件\n");
				*running = false;
				break;

			case SDL_EVENT_KEY_DOWN:
				// 键盘按下事件
				if (event.key.key == SDLK_ESCAPE) {
					printf("按下ESC键，退出程序\n");
					*running = false;
				}
				break;
		}
	}
}

int main(int argc, char* argv[]) {
	SDL_Window* window = Game_Init();
	if (window == NULL) {
		printf("游戏初始化失败，程序退出\n");
		return -1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

	if (renderer == NULL) {
		printf("创建渲染器失败: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	printf("渲染器创建成功!\n");

	bool running = true;
	SDL_Windows_ESC_Event_Check(&running);
	SDL_FRect rect = {
		.x = 350, // X坐标
		.y = 250, // Y坐标
		.w = 100, // 宽度
		.h = 100  // 高度
	};
	printf("进入主循环，按关闭按钮或ESC键退出...\n");

	while (running) {
		SDL_Windows_ESC_Event_Check(&running);
		// ----------------------------------------
		// 4.2 清屏（设置背景色）
		// 颜色格式：R, G, B, A (0-255)
		// ----------------------------------------
		SDL_SetRenderDrawColor(renderer, 50, 100, 150, 255); // 蓝灰色背景
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // 白色

		const bool* keyboardState = SDL_GetKeyboardState(NULL);
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

	// ========================================
	// 第5步：清理资源
	// 这就像嵌入式中的外设去初始化
	// ========================================
	printf("正在清理资源...\n");
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	printf("程序正常退出!\n");
	return 0;
}
