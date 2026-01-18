
#include <text.h>

bool initialize_ttf() {
	// SDL3_ttf: TTF_Init() 返回 bool，成功返回 true
	if (!TTF_Init()) {
		printf("TTF_Init failed: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

void shutdown_ttf() {
	TTF_Quit();
}

TTF_Font* load_font(const char* font_path, int font_size) {
	TTF_Font* font = TTF_OpenFont(font_path, font_size);
	if (font == NULL) {
		printf("TTF_OpenFont failed: %s\n", SDL_GetError());
	}
	return font;
}

void close_font(TTF_Font* font) {
	if (font) {
		TTF_CloseFont(font);
	}
}

void Text_Draw(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, float x,
			   float y) {
	if (font == NULL || text == NULL) {
		return;
	}

	// 渲染文本到表面
	SDL_Surface* text_surface = TTF_RenderText_Blended(font, text, 0, color);
	if (text_surface == NULL) {
		printf("TTF_RenderText_Blended failed: %s\n", SDL_GetError());
		return;
	}

	// 创建纹理
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	if (text_texture == NULL) {
		printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		SDL_DestroySurface(text_surface); // SDL3: 改名了
		return;
	}

	// 设置目标矩形
	SDL_FRect dst_rect = {x, y, (float)text_surface->w, (float)text_surface->h};

	// 复制纹理到渲染器
	SDL_RenderTexture(renderer, text_texture, NULL, &dst_rect); // SDL3: 改名了

	// 清理
	SDL_DestroyTexture(text_texture);
	SDL_DestroySurface(text_surface); 
}