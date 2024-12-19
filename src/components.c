#include "components.h"

typedef struct {
    const char *text;
    TTF_Font *font;
    SDL_Texture *textTexture;
    SDL_Color bgColor;
    SDL_Color textColor;
} ButtonContext;

const WGT_VTable buttonVTable = {
    .onResize = NULL,
    .onMove = NULL,
    .onEvent = NULL,
    .onDraw = NULL,
    .onDestroy = NULL,
};

WGT_Widget* WGT_CreateButton(const char *text, TTF_Font *font, SDL_Color bgColor, SDL_Color textColor) {
    WGT_Widget *widget;
    ButtonContext *context = WGT_MakeWidget(&widget, &buttonVTable, sizeof(ButtonContext));
    *context = (ButtonContext) {
        .text = text,
        .font = font,
        .textTexture = NULL,
        .bgColor = bgColor,
        .textColor = textColor,
    };
    return widget;
}