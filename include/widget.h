#ifndef WIDGET_T
#define WIDGET_T

#include <SDL_rect.h>
#include <SDL_events.h>
#include <SDL_render.h>

// Order of fields is not accidental
// Fields can be `NULL` to indicate not implemented
typedef struct {
    void (*onResize)(void *ctx, SDL_Rect newRect);
    void (*onMove)(void *ctx, SDL_Rect newRect);
    void (*onEvent)(void *ctx, SDL_Rect rect, SDL_Event event);
    int (*onDraw)(void *ctx, SDL_Rect rect, SDL_Renderer *renderer); // Return none 0 for error
    void (*onDestroy)(void *ctx);
} WGT_VTable;

typedef struct WGT_Widget WGT_Widget;

/// Helper function to allocate memory with a `WGT_Widget` header
/// Only used when creating your own `WGT_CreateX` function
/// @param widget Pointer to `WGT_Widget*`; Points to head of the widget
/// @param vtable Pointer to VTable; Fields in VTable can be `NULL`
/// @param size Size of allocation
/// @returns Pointer to allocated memory
void* WGT_MakeWidget(WGT_Widget **widget, const WGT_VTable *vtable, size_t size);

// Returns the context allocated by `WGT_AllocWidget`
void* WGT_GetContext(WGT_Widget *widget);

// Propogate SDL events to child widgets
void WGT_SendEvent(WGT_Widget *widget, SDL_Event event);
// Must call both `WGT_SetPosition` and `WGT_SetSize` at least once before calling
// Calls `SDL_RenderSetClipRect`
void WGT_Draw(SDL_Renderer *renderer, WGT_Widget *widget);
// Resizes widget; Calls `onResize` from `WGT_VTable`
// Checks if the size is different, if not, does nothing
void WGT_SetSize(WGT_Widget *widget, SDL_Point newSize);
// Repositions the widget for `WGT_Draw`; Calls `onDestroy` from `WGT_VTable`
// Checks if the position is new, if not, does nothing
void WGT_SetPosition(WGT_Widget *widget, SDL_Point newPosition);
// Calls `onDestroy` from `WGT_VTable`
void WGT_Destroy(WGT_Widget *widget);

#endif