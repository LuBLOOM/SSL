#include "../include/ui.h"

void ui_init(const char *title, const unsigned w, const unsigned h, const unsigned flags)
{
	ui_active = 1;
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);
	context = SDL_GL_CreateContext(window);
	glewInit();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, w, h, 0.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0.0, 0.0, w, h);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	
	glEnable(GL_TEXTURE_2D);
}

void ui_render_start(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void ui_render_end(void)
{
	SDL_GL_SwapWindow(window);
}

void ui_events(SDL_Event event)
{
	if (event.type == SDL_QUIT) {
		ui_active = 0;
	} else if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			ui_active = 0;
		}
	}
}

void ui_free(void)
{
	ui_active = 0;
	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(context);
	SDL_Quit();
}
