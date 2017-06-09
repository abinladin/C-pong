/*
* Author: Abdullah Binladin
* Date: 22 May 2017
*/

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture* Graphics_LoadTexture(SDL_Renderer* rend, char* path){
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	
        /*
        * It would have been better if the executable was located in /C-pong/, rather than /C-pong/run/. If that were
        * the case, then I would not need to dynamically allocate memory here (It would also be the standard). However, 
        * this program is a portfolio piece and as such, I wished to showcase my knowledge of the C language.
        */
        
	char* topDir = "../";
	char* relPath = malloc(sizeof topDir + sizeof path);
	
	strcpy(relPath, topDir);
	strcat(relPath, path);

	surface = IMG_Load(relPath);
	free(relPath);
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
