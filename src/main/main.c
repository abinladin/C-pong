/*
* Author: Abdullah Binladin
* Date: 21 May 2017
*/

#include <stdio.h>
#include <SDL2/SDL.h>
#include "../graphics/graphics.h"
#include "../gameobject/gameobject.h"
#define LOG(x) printf("%s SDL_Error: %s\n", x, SDL_GetError())

//function prototypes
int initSDL();
int initWindow();
int initRenderer();
int loadMedia();
void closeSDL();

//Window constants
const int WIDTH = 600;
const int HEIGHT = 600;
const char TITLE[] = "pong";
SDL_Window* window = NULL;
SDL_Renderer* rend = NULL;

//Game constants
const int FPS = 30;

//textures to be loaded
SDL_Texture* background = NULL;
SDL_Texture* paddleTexture = NULL;
SDL_Texture* puckTexture = NULL;

int initSDL(){
    int initFlags = SDL_INIT_VIDEO;
    if (SDL_Init(initFlags) != 0){
        LOG("Failed to init SDL!");
        return 1;
    };
    printf("initSDL() successful!\n");
    return 0;
}

int initWindow(){
    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL){
        LOG("Failed to create window!");
        SDL_Quit();
        return 1;
    }
    printf("initWindow() successful!\n");
    return 0;
}

int initRenderer(){
    int rendFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    rend = SDL_CreateRenderer(window, -1, rendFlags);
    if (rend == NULL){
        LOG("Failed to create renderer!");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    printf("initRenderer() successful!\n");
    return 0;
}

int loadMedia(){
    background = Graphics_LoadTexture(rend, "res/wood.png");
    paddleTexture = Graphics_LoadTexture(rend, "res/paddle.png");
    puckTexture = Graphics_LoadTexture(rend, "res/puck.png");

    if(background == NULL || paddleTexture == NULL || puckTexture == NULL){
        printf("Failed to load media!\n");
        closeSDL();
        return 1;
    }
    printf("loadMedia() successful!\n");
    return 0;
}

void closeSDL(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(rend);

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(paddleTexture);
    SDL_DestroyTexture(puckTexture);

    SDL_Quit();
}

int main(){
    //initialization
    if (initSDL() != 0) return 1;
    if (initWindow() != 0) return 1;
    if (initRenderer() != 0) return 1;
    if (loadMedia() != 0) return 1;

    //create GameObjects
    int objHeight = 0;
    int objWidth = 0;
    int paddleSpeed  = FPS/3;
    int puckSpeed = FPS/4;
    SDL_QueryTexture(paddleTexture, NULL, NULL, &objWidth, &objHeight);

    struct GameObject player = createGameObject(paddleTexture, "player", objWidth, HEIGHT/2 - objHeight/2, paddleSpeed);
    struct GameObject cpu = createGameObject(paddleTexture, "cpu", WIDTH - (2 * objWidth), HEIGHT/2 - objHeight/2, paddleSpeed);

    SDL_QueryTexture(puckTexture, NULL, NULL, &objWidth, &objHeight);
    struct GameObject puck = createGameObject(puckTexture, "puck", WIDTH/2 - objWidth/2, HEIGHT/2 - objHeight/2, puckSpeed);
    
    //init puck movement
    puck.direction.moveLeft = 1;
    puck.direction.moveUp = 1;
    
    //game loop
    const int WINNING_POINTS = 7;
    int quit = 0;
    
    //player variables	
    int mouseY = 0;
    int playerPoints = 0;
    
    //CPU variables
    int cpuPoints = 0;
    
    while (!quit){
        SDL_RenderClear(rend);
        //handle exit logic
        {
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0){
                if(e.type == SDL_QUIT) quit = 1;
            }
        }

        //Update player position
        SDL_GetMouseState(NULL, &mouseY);
        updatePaddleDirection(&player, mouseY, HEIGHT);

        //update cpu position
        int centerPuckY = puck.bounds.y + puck.bounds.h/2;
        int centerPuckX = puck.bounds.x + puck.bounds.w/2;
        int difficulty = WIDTH * 3/4;
        
        if (centerPuckX > difficulty){
        	updatePaddleDirection(&cpu, centerPuckY, HEIGHT);
		}
		
        //update puck position and points
        int pointFlag = updatePuckDirection(&puck, WIDTH, HEIGHT);
        
        if (pointFlag != 0){
        
		    if (pointFlag == 1){
		    	cpuPoints++;
		    }
		    
		    if (pointFlag == 2){
		    	playerPoints++;
		    }
		    
		    printf("Player Points: %d\nCPU Points: %d\n\n", playerPoints, cpuPoints);
		    if (playerPoints >= WINNING_POINTS || cpuPoints >= WINNING_POINTS){
		    	quit = 1;
		    }	    
		}

        //handle puck intersection
        handleGameObjectIntersection(&puck, &player);
        handleGameObjectIntersection(&puck, &cpu);

        //draw GameObjects to the screen
        SDL_RenderCopy(rend, background, NULL, NULL);
        SDL_RenderCopy(rend, player.texture, NULL, &player.bounds);
        SDL_RenderCopy(rend, cpu.texture, NULL, &cpu.bounds);
        SDL_RenderCopy(rend, puck.texture, NULL, &puck.bounds);

        SDL_RenderPresent(rend);
        
    } // end of game loop
    
    destroyGameObject(&player);
    destroyGameObject(&cpu);
    destroyGameObject(&puck);
    
    closeSDL();
    return 0;
}


