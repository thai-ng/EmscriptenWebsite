// CppWeb.cpp : Defines the entry point for the application.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* imageTexture = nullptr;

void render_func()
{
	printf("drawing!\n");
	if (imageTexture) 
	{
		SDL_RenderCopy(renderer, imageTexture, nullptr, nullptr);
	} 
	else
	{
		for (int i = 0; i < 256; i++) {
			for (int j = 0; j < 256; j++) {
				int alpha = (i + j) % 255;
				SDL_SetRenderDrawColor(renderer, i, j, 255 - i, alpha);
				SDL_RenderDrawPoint(renderer, i, j);
			}
		}
	}

	SDL_RenderPresent(renderer);
#ifdef __EMSCRIPTEN__
	emscripten_cancel_main_loop();
#endif
}

int main(int argc, char** argv) {
	printf("hello, world!\n");

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(256, 256, 0, &window, &renderer);
	
	auto init = IMG_Init(IMG_INIT_PNG);
	auto surface = IMG_Load("assets/test.png");
	if (surface) 
	{
		SDL_CreateWindowAndRenderer(surface->w, surface->h, 0, &window, &renderer);
		imageTexture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_UnlockSurface(surface);
	} 
	else
	{
		SDL_CreateWindowAndRenderer(256, 256, 0, &window, &renderer);
		printf("Couldn't open image, Error: %s\n", IMG_GetError());
	}

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(render_func, 0, 1);
#else
	render_func();
#endif
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}