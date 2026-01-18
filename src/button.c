#include "SDL3/SDL_events.h"
#include "SDL3/SDL_stdinc.h"
#include <button.h>

Button* button_init(float x, float y, float w, float h, Button_Color colors, int (*on_click)(void **argv), int (*on_release)(void **argv)) {
    Button* button = (Button*)malloc(sizeof(Button));
    if (!button) {
        return NULL;
    }
    button->rect.x = x;
    button->rect.y = y;
    button->rect.w = w;
    button->rect.h = h;
    button->colors = colors;
    button->is_pressed = false;
    button->on_click = on_click;
    button->on_release = on_release;
    button->update = button_update;
    return button;
}

Button* button_init_with_font(float x, float y, float w, float h, Button_Color colors,
                                int (*on_click)(void **argv), int (*on_release)(void **argv), 
                                TTF_Font* font, const char* text, SDL_Color color) {
    int text_width;
    int text_height;
    TTF_GetStringSize(font, text, 0,&text_width, &text_height);
    if(text_width == 0 || text_height == 0){
        printf("Failed to get text dimensions for button\n");
    }
    if(w < text_width){
        w = text_width; // 添加一些内边距
    }
    Button* button = button_init(x, y, w, h, colors, on_click, on_release);
    button->update = button_update_with_text;
    button->text.font = font;
    button->text.text = text;
    button->text.color = color;
    button->text.x = x + (w - text_width) / 2; // 水平居中
    button->text.y = y + (h - text_height) / 2; // 垂直居中
    return button;
}

int button_deinit(Button* button) {
    if (button) {
        free(button);
        return 0;
    }
    return -1;
}

void button_handle_event(Button* button, SDL_Event *event) {
    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        float mouse_x = event->button.x;
        float mouse_y = event->button.y;
        if (mouse_x >= button->rect.x && mouse_x <= button->rect.x + button->rect.w &&
            mouse_y >= button->rect.y && mouse_y <= button->rect.y + button->rect.h) {
            button->is_pressed = true;
            if (button->on_click) {
                if(button->on_click(button->on_click_args.argv)){
                    printf("Button click handler returned error\n");
                }
            }
        }
    } else if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
        if (button->is_pressed) {
            button->is_pressed = false;
            if (button->on_release) {
                if(button->on_release(button->on_release_args.argv)){
                    printf("Button release handler returned error\n");
                }
            }
        }
    }
}

void button_update(Button* button, SDL_Renderer *renderer) {
    // 绘制按钮
    SDL_SetRenderDrawColor(renderer, button->colors.components.r, button->colors.components.g, button->colors.components.b, button->colors.components.a);
    SDL_RenderFillRect(renderer, &button->rect);
}

void button_update_with_text(Button* button, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, button->colors.components.r, button->colors.components.g, button->colors.components.b, button->colors.components.a);
    SDL_RenderFillRect(renderer, &button->rect);
    Text_Draw(renderer, button->text.font, button->text.text, button->text.color, button->text.x, button->text.y); // 按钮上的文字
}
