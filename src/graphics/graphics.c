#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture* Graphics_LoadTexture(SDL_Renderer* rend, char* path){
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	
	surface = IMG_Load(path);
	if(surface == NULL){
		printf("[Surface] failed to load %s! SDL_Error: %s", path, SDL_GetError());
		return NULL;
	}
	
	texture = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	if(texture == NULL){
		printf("[Texture] failed to load %s! SDL_Error: %s", path, SDL_GetError());
		return NULL;
	}
	
	return texture;
}
