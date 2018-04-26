// CppWeb.cpp : Defines the entry point for the application.
//

#include <stdio.h>
#include <SDL2/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

SDL_Window* window;
SDL_Renderer* renderer;

void render_func()
{
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			int alpha = (i + j) % 255;
			SDL_SetRenderDrawColor(renderer, i, j, 255 - i, alpha);
			SDL_RenderDrawPoint(renderer, i, j);
		}
	}

#ifdef __EMSCRIPTEN__
	emscripten_cancel_main_loop();
#endif
}

int main(int argc, char** argv) {
	printf("hello, world!\n");


	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(256, 256, 0, &window, &renderer);

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(render_func, 60, 1);
#else
	render_func();
#endif

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}