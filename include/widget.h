#ifndef WGT_WIDGET_T
#define WGT_WIDGET_T

#include <SDL_rect.h>
#include <SDL_events.h>
#include <SDL_render.h>

typedef struct WGT_VTable WGT_VTable;

struct WGT_VTable {
    void (*onEvent)(void *ctx, SDL_Rect rect, SDL_Event event);
    void (*onDraw)(void *ctx, SDL_Rect rect, SDL_Renderer *renderer);
    void (*onResize)(void *ctx, SDL_Rect newRect);
    void (*onDestroy)(void *ctx);
};

typedef struct WGT_Widget WGT_Widget;

// Helper function to create a virtual object
// Only used when creating your own `WGT_CreateX` function
// \param **ctx Reference to pointer to context; becomes a pointer to allocated memory
// \param size Size of context
WGT_Widget* WGT_MakeWidget(WGT_VTable vtable, void **ctx, size_t size);
void* WGT_GetContext(WGT_Widget *widget);

// Propogate SDL events to child widgets
void WGT_PassEvent(WGT_Widget *widget, SDL_Event event);
// Must call both `WGT_SetPosition` and `WGT_SetSize` at least once before calling
void WGT_Draw(SDL_Renderer *renderer, WGT_Widget *widget);
// Resizes widget, calls `onResize` from `WGT_VTable`
// Checks if the size is different, if not, does nothing
void WGT_SetSize(WGT_Widget *widget, SDL_Point newSize);
// Repositions the widget for `WGT_Draw`; does nothing special
void WGT_SetPosition(WGT_Widget *widget, SDL_Point newPosition);
// Calls `onDestroy` on the widget
void WGT_Destroy(WGT_Widget *widget);

#endif