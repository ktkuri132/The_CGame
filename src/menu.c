#include "SDL3/SDL_pixels.h"
#include "button.h"
#include <menu.h>
#include <text.h>

Menu* menu_init(const char* title, float x, float y, float w, float h, TTF_Font* font,
				SDL_Color title_color, SDL_Color background_color) {
	Menu* menu = (Menu*)malloc(sizeof(Menu));
	if (!menu) {
		return NULL;
	}

	// 初始化按钮数组为NULL（重要！）
	for (int i = 0; i < 10; i++) {
		menu->buttons[i] = NULL;
	}

	menu->title.text = title;
	menu->title.font = font;
	menu->title.color = title_color;
	menu->rect.x = x;
	menu->rect.y = y;
	menu->rect.w = w;
	menu->rect.h = h;
	menu->background_color.normal = background_color;
	menu->update = menu_update;
	int text_width;
	int text_height;
	TTF_GetStringSize(menu->title.font, menu->title.text, 0, &text_width, &text_height);
	if (text_width == 0 || text_height == 0) {
		printf("Failed to get text dimensions for button\n");
	}
	if (w < (float)text_width) {
		w = (float)text_width; // 添加一些内边距
	}
	menu->title.x = x + (w - (float)text_width) / 2; // 水平居中
	return menu;
}

int menu_deinit(Menu* menu) {
	if (menu) {
		free(menu);
		return 0;
	}
	return -1;
}

int menu_register_button(Menu* menu, Button* button) {
	if (menu == NULL || button == NULL) {
		return -1;
	}
	// 找到第一个空位
	int i = 0;
	while (menu->buttons[i] != NULL && i < 10) { // 假设最多10个按钮
		i++;
	}
	if (i >= 10) {
		printf("菜单按钮数量已达上限\n");
		return -1;
	}
	menu->buttons[i] = button;
	// 设置按钮X坐标居中（相对于菜单）
	menu->buttons[i]->rect.x = menu->rect.x + (menu->rect.w - button->rect.w) / 2;
	printf("注册按钮 %d: %s\n", i, button->text.text);
	return 0;
}

void menu_update(Menu* menu, SDL_Renderer* renderer) {
	// 绘制菜单背景
	SDL_SetRenderDrawColor(renderer, menu->background_color.components.r,
						   menu->background_color.components.g, menu->background_color.components.b,
						   menu->background_color.components.a);
	SDL_RenderFillRect(renderer, &menu->rect);

	// 绘制菜单标题
	Text_Draw(renderer, menu->title.font, menu->title.text, menu->title.color, menu->title.x,
			  menu->rect.y + 10);

	// 绘制菜单按钮
	for (int i = 0; menu->buttons[i] != NULL; i++) {
		menu->buttons[i]->update(menu->buttons[i], renderer);
	}
}

void menu_handle_event(Menu* menu, SDL_Event* event) {
	for (int i = 0; menu->buttons[i] != NULL; i++) {
		button_handle_event(menu->buttons[i], event);
	}
}


