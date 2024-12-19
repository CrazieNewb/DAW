#include "widget.h"

struct WGT_Widget {
    const WGT_VTable *vtable;
    SDL_Rect rect;
    const char **label;
};

void* WGT_MakeWidget(WGT_Widget **widget, const WGT_VTable *vtable, size_t size) {
    *widget = malloc(sizeof(WGT_Widget) + size);
    (*widget)->vtable = vtable;
    (*widget)->rect = (SDL_Rect){0};
    void* ctx = widget + 1;
    return ctx;
}

void* WGT_GetContext(WGT_Widget *widget) {
    return (widget + 1);
}

void WGT_SendEvent(WGT_Widget *widget, SDL_Event event) {
    if (widget->vtable->onEvent != NULL) {
        (widget->vtable->onEvent)(WGT_GetContext(widget), widget->rect, event);
    }
}

void WGT_Draw(SDL_Renderer *renderer, WGT_Widget *widget) {
    SDL_RenderSetClipRect(renderer, &widget->rect);
    int errorCode = -1;
    if (widget->vtable->onDraw != NULL) {
        errorCode = (widget->vtable->onDraw)(WGT_GetContext(widget), widget->rect, renderer);
    }
    if (errorCode != 0) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 100, 0);
        SDL_RenderClear(renderer);
    }
    SDL_RenderSetClipRect(renderer, NULL);
}

void WGT_SetSize(WGT_Widget *widget, SDL_Point newSize) {
    if (widget->rect.w == newSize.x && widget->rect.h == newSize.y) {
        return;
    }
    widget->rect.w = newSize.x;
    widget->rect.h = newSize.y;
    if (widget->vtable->onResize != NULL) {
        (widget->vtable->onResize)(WGT_GetContext(widget), widget->rect);
    }
}

void WGT_SetPosition(WGT_Widget *widget, SDL_Point newPosition) {
    if (widget->rect.x == newPosition.x && widget->rect.x == newPosition.y) {
        return;
    }
    widget->rect.x = newPosition.x;
    widget->rect.y = newPosition.y;
    if (widget->vtable->onMove != NULL) {
        (widget->vtable->onMove)(WGT_GetContext(widget), widget->rect);
    }
}

void WGT_Destroy(WGT_Widget *widget) {
    if (widget->vtable->onDestroy != NULL) {
        (widget->vtable->onDestroy)(WGT_GetContext(widget));
    }
    free(widget);
}