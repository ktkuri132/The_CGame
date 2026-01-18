#include "SDL3/SDL_pixels.h"
#include "control_system.h"
#include "menu.h"

Menu* control_panel_init() {
	printf("Control panel function called.\n");
	TTF_Font* font = load_font("./assets/fonts/refsan.ttf", 32);
	SDL_Color white = {255, 255, 255, 255};
	SDL_Color yellow = {255, 255, 0, 255};
	SDL_Color red = {255, 0, 0, 255};
	SDL_Color blue = {0, 0, 255, 255};
	Button_Color red_color = {.normal = red};
	Button_Color yellow_color = {.normal = yellow};
	Button_Color white_color = {.normal = white};
	Menu* panel_menu = menu_init("Control Panel", 50, 50, 300, 400, font, white, blue);
	Button* start_button =
		button_init_with_font(100, 100, 200, 50, white_color, NULL, NULL, font, "Start", red);
	Button* exit_button =
		button_init_with_font(100, 200, 200, 50, white_color, NULL, NULL, font, "Exit", red);
	menu_register_button(panel_menu, start_button);
	menu_register_button(panel_menu, exit_button);
	return panel_menu;
}

int menu_button_click(void** argv) {
	Button* button = (Button*)argv[0];
	SDL_Renderer* renderer = (SDL_Renderer*)argv[1];
	printf("按钮被点击！\n");
	SDL_Color highlight = {255, 255, 0, 255};
	button->text.color = highlight;
	return 0;
}

int menu_button_release(void** argv) {
	printf("按钮被释放！\n");
	Button* button = (Button*)argv[0];
	SDL_Renderer* renderer = (SDL_Renderer*)argv[1];
	bool* running = (bool*)argv[2];
	SDL_Color normal = {255, 0, 0, 255};
	button->text.color = normal;
	*running = false;
	button->update(button, renderer);
	SDL_Delay(100);
	return 0;
}
