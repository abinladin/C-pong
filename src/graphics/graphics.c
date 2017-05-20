#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "graphics.h"

SDL_Texture* Graphics_LoadTexture(SDL_Renderer* rend, char* path){
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;

    char* resDir = "../";
    char* relPath = malloc(sizeof resDir + sizeof path + 1);
    
    strcpy(relPath, resDir);
    strcat(relPath, path);

    surface = IMG_Load(relPath);
    
    if (surface == NULL){
        printf("[Surface] Failed to load %s! SDL_GetError: %s\n", relPath, SDL_GetError());
        free(relPath);
        return NULL;
    }

    texture = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    if(texture == NULL){
        printf("[Texture] Failed to load %s!\n", relPath);
        return NULL;
    }
    free(relPath);
    return texture;
}
