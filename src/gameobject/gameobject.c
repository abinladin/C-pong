#include <SDL2/SDL.h>
#include "gameobject.h"
#define CHECKING_OPTIMIZATION 0

struct GameObject createGameObject(SDL_Texture* texture, char* name, int initX, int initY, int speed){  
    struct GameObject obj;
    obj.texture = texture;
    obj.bounds.x = initX;
    obj.bounds.y = initY;
    obj.speed = speed;
    SDL_QueryTexture(texture, NULL, NULL, &obj.bounds.w, &obj.bounds.h);

    obj.direction.moveUp = 0;
    obj.direction.moveDown = 0;
    obj.direction.moveLeft = 0;
    obj.direction.moveRight = 0;
    
    obj.name = malloc(sizeof name);
    strcpy(obj.name, name);
	printf("%s created!\n", obj.name);
    return obj;
}


void destroyGameObject(struct GameObject* obj){
    SDL_DestroyTexture(obj->texture);
    free(obj->name);
}



void updatePaddleDirection(struct GameObject* obj, int dependency, int heightBound){  
    int dy = obj->bounds.h / 8;
    if (strcmp(obj->name, "cpu") == 0){
        dy = obj->bounds.h / 4;
    }

    if (obj->bounds.y < 0) obj->bounds.y = 0;
    if (obj->bounds.y > heightBound - obj->bounds.h) obj->bounds.y = heightBound - obj->bounds.h;

    if (dependency < obj->bounds.y + obj->bounds.h/2 -dy){
        obj->direction.moveUp = 1;
        obj->direction.moveDown = 0;
    } else if (dependency > obj->bounds.y + obj->bounds.h/2 + dy){
        obj->direction.moveUp = 0;
        obj->direction.moveDown = 1;
    } else {
        obj->direction.moveUp = 0;
        obj->direction.moveDown = 0;
    }

    if (obj->direction.moveUp){
        obj->bounds.y -= obj->speed;
    }

    if (obj->direction.moveDown){
        obj->bounds.y += obj->speed;
    }
}


//[debug] Counters that will count how often statements int updatePuckDirection() are called:
#if CHECKING_OPTIMIZATION
int touchLeftWindowEdge = 0;
int touchRightWindowEdge = 0;
int touchTopWindowEdge = 0;
int touchBottomWindowEdge = 0;

void printTrackedVariables(){
    printf("PaddleTouches:\n Left: %d\n Right: %d\n Top: %d\n Bottom: %d\n", touchLeftWindowEdge, touchRightWindowEdge, touchTopWindowEdge, touchBottomWindowEdge);
	for (int i = 0; i < 10; i++) printf("\n");
}
#endif
int updatePuckDirection(struct GameObject* obj, int widthBound, int heightBound){ 
    
    //conditions ordered from most likely to least likely

    if (obj->bounds.y < 0){

        #if CHECKING_OPTIMIZATION
        touchTopWindowEdge++;
        printTrackedVariables();
        #endif

    	obj->bounds.y = 1;
        obj->direction.moveDown = 1;
        obj->direction.moveUp = 0;
        return 0;
    }

    if (obj->bounds.y > heightBound - obj->bounds.h){

        #if CHECKING_OPTIMIZATION
        touchBottomWindowEdge++;
        printTrackedVariables();
        #endif

    	obj->bounds.y = heightBound - obj->bounds.h-1;
        obj->direction.moveDown = 0;
        obj->direction.moveUp = 1;
        return 0;
    }
    
    if (obj->bounds.x < 0 - obj->bounds.w){

        #if CHECKING_OPTIMIZATION
        touchLeftWindowEdge++;
        printTrackedVariables();
        #endif

        obj->bounds.x = widthBound/2 - obj->bounds.w/2;
        obj->bounds.y = heightBound/2 - obj->bounds.h/2;
        obj->direction.moveLeft = 0;
        obj->direction.moveRight = 1;
        return 1;
    }

    if (obj->bounds.x > widthBound){  

        #if CHECKING_OPTIMIZATION
        touchRightWindowEdge++;
        printTrackedVariables();
        #endif

        obj->bounds.x = widthBound/2 - obj->bounds.w/2;
        obj->bounds.y = heightBound/2 - obj->bounds.h/2;

        obj->direction.moveLeft = 1;
        obj->direction.moveRight = 0;
        return 2;
    }

	//update object position
    if (obj->direction.moveUp) {
    	obj->bounds.y += -obj->speed;
    }
    
    if (obj->direction.moveDown){
    	obj->bounds.y += obj->speed;
    }
    
    if (obj->direction.moveLeft) {
    	obj->bounds.x += -obj->speed;
    }
    
    if (obj->direction.moveRight) {
    	obj->bounds.x += obj->speed;
    }
    
    return 0;
}



void handleGameObjectIntersection(struct GameObject* puck, struct GameObject* paddle){
	if ( strcmp(paddle->name, "player") == 0 && SDL_HasIntersection(&puck->bounds, &paddle->bounds) == SDL_TRUE ){
		puck->direction.moveLeft = 0;
		puck->direction.moveRight = 1;
		if (paddle->direction.moveUp){
			puck->direction.moveUp = 1;
			puck->direction.moveDown = 0;
		}
		if (paddle->direction.moveDown){
			puck->direction.moveUp = 0;
			puck->direction.moveDown = 1;
		}
	}
  	
  	if ( strcmp(paddle->name, "cpu") == 0 && SDL_HasIntersection(&puck->bounds, &paddle->bounds) == SDL_TRUE){
		puck->direction.moveLeft = 1;
		puck->direction.moveRight = 0;
		if (paddle->direction.moveUp){
			puck->direction.moveUp = 1;
			puck->direction.moveDown = 0;
		}
		if (paddle->direction.moveDown){
			puck->direction.moveUp = 0;
			puck->direction.moveDown = 1;
		}
	}
}




