#ifndef WIDGET_COMPONENTS_T
#define WIDGET_COMPONENTS_T

#include "widget.h"
#include <SDL_ttf.h>

WGT_Widget* WGT_CreateButton(const char *text, TTF_Font *font, SDL_Color bgColor, SDL_Color textColor);

#endif