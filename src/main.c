/**
 * 我的第一个SDL3程序
 *
 * 这个程序会创建一个窗口，就像嵌入式开发中初始化LCD屏幕一样
 */

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_thread.h"
#include "control_system.h"
#include "menu.h"
#include "test.h"
#include "text.h"


// 共享数据（线程间通信）
typedef struct {
	bool running;
	bool button_pressed;
	float sensor_value;
	SDL_Mutex* mutex; // 互斥锁，保护共享数据
} SharedData;

SharedData g_shared = {0};

SDL_Window* System_Init() {
	SetConsoleOutputCP(65001);
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		printf("SDL初始化失败: %s\n", SDL_GetError());
		return NULL;
	}
	printf("SDL3 初始化成功!\n");
	static SDL_Window* window;
	window = SDL_CreateWindow("Control System Box", // 窗口标题
							  WINDOW_WIDTH,			// 宽度
							  WINDOW_HEIGHT,		// 高度
							  0						// 窗口标志（0表示默认）
	);

	if (window == NULL) {
		printf("创建窗口失败: %s\n", SDL_GetError());
		SDL_Quit();
		return NULL;
	}
	printf("窗口创建成功!\n");
	return window;
}

void SDL_Windows_ESC_Event_Check(bool* running, SDL_Event event) {
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
	SDL_Window* window = System_Init();
	if (window == NULL) {
		printf("系统框架初始化失败，程序退出\n");
		return -1;
	}

	SDL_Event event;
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
	if (renderer == NULL) {
		printf("创建渲染器失败: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	printf("渲染器创建成功!\n");

	TTF_Font* font;
	if (!initialize_ttf()) {
		printf("TTF初始化失败，程序退出\n");
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		shutdown_ttf();
		SDL_Quit();
		return -1;
	}

	bool running = true;
	Mouse_State mouse_state = {};
	printf("进入主循环，按关闭按钮或ESC键退出...\n");
	const bool* keyboardState;
	g_shared.mutex = SDL_CreateMutex();
	g_shared.running = true;

	// 在主线程中初始化控制面板（不要用子线程渲染！）
	Menu* panel_menu = control_panel_init();

	while (running) {
		// 事件处理
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
				running = false;
			}
			// 把事件传给菜单处理
			menu_handle_event(panel_menu, &event);
		}

		// 渲染背景
		SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
		SDL_RenderClear(renderer);

		// 更新并绘制控制面板
		panel_menu->update(panel_menu, renderer);

		SDL_RenderPresent(renderer);
		SDL_Delay(10);
	}

	// 清理
	menu_deinit(panel_menu);
	printf("正在清理资源...\n");
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	printf("程序正常退出!\n");
	return 0;
}
