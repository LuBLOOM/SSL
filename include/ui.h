#ifndef __SSL_UI_H
#define __SSL_UI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define UI_WINDOW_NAME "SSL - Simple Shader Lab"
#define UI_WINDOW_WIDTH 1200
#define UI_WINDOW_HEIGHT 800
#define UI_WINDOW_FLAGS (SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL)

SDL_Window *window;
SDL_GLContext *context;
unsigned char ui_active;

void ui_init(const char *, const unsigned, const unsigned, const unsigned);
void ui_render_start(void);
void ui_render_end(void);
void ui_events(SDL_Event);
void ui_free(void);

#endif /* __SSL_UI_H */
