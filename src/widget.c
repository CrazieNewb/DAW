#include "widget.h"
#include <stdlib.h>

struct WGT_Widget {
    WGT_VTable vtable;
    SDL_Rect rect;
};

WGT_Widget* WGT_MakeWidget(WGT_VTable vtable, void **ctx, size_t size) {
    WGT_Widget *widget = malloc(sizeof(WGT_Widget) + size);
    widget->vtable = vtable;
    widget->rect = (SDL_Rect){0};
    *ctx = widget + 1;
    return widget;
}

void* WGT_GetContext(WGT_Widget *widget) {
    return (widget + 1);
}

void WGT_PassEvent(WGT_Widget *widget, SDL_Event event) {
    if (widget->vtable.onEvent != NULL) {
        (widget->vtable.onEvent)(WGT_GetContext(widget), widget->rect, event);
    }
}

void WGT_Draw(SDL_Renderer *renderer, WGT_Widget *widget) {
    SDL_RenderSetClipRect(renderer, &widget->rect);
    if (widget->vtable.onDraw != NULL) {
        (widget->vtable.onDraw)(WGT_GetContext(widget), widget->rect, renderer);
    }
    SDL_RenderSetClipRect(renderer, NULL);
}

void WGT_SetSize(WGT_Widget *widget, SDL_Point newSize) {
    if (widget->rect.w == newSize.x && widget->rect.h == newSize.y) {
        return;
    }
    widget->rect.w = newSize.x;
    widget->rect.h = newSize.y;
    if (widget->vtable.onResize != NULL) {
        (widget->vtable.onResize)(WGT_GetContext(widget), widget->rect);
    }
}

void WGT_SetPosition(WGT_Widget *widget, SDL_Point newPosition) {
    widget->rect.x = newPosition.x;
    widget->rect.y = newPosition.y;
}

void WGT_Destroy(WGT_Widget *widget) {
    if (widget->vtable.onDestroy != NULL) {
        (widget->vtable.onDestroy)(WGT_GetContext(widget));
    }
    free(widget);
}