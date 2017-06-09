/*
* Author: Abdullah Binladin
* Date: 22 May 2017
*/

#include <SDL2/SDL.h>

typedef struct GameObject{
    SDL_Texture* texture;
    SDL_Rect bounds;
    char* name;
    int speed;
    struct Direction {
        int moveUp;
        int moveDown;
        int moveLeft;
        int moveRight;
    } direction;
} GameObject;

struct GameObject createGameObject(SDL_Texture* texture, char* name, int initX, int initY, int speed);
void destroyGameObject(struct GameObject* obj);
void updatePaddleDirection(struct GameObject* obj, int dependency, int heightBound);
int updatePuckDirection(struct GameObject* obj, int widthBound, int heightBound);
void handleGameObjectIntersection(struct GameObject* puck, struct GameObject* paddle);
