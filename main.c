#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL2/SDL_stdinc.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "structs.h"
#include "defs.h"
#include "draw.c"
#include "init.c"
#include "input.c"
#include "menu.c"
#include "snake.c"
#include "apple.c"
#include "cleanup.c"

int main(int argc, char *argv[]) {

    memset(&app, 0, sizeof(App));
    initSDL();
    TTF_Init();
    
    initTextures();
    initSnake();
    initApple();

    atexit(cleanup);


    while(1) {
        prepareScene();
        input();
        menu();
        move();
        showScore();
        drawApple();
        drawSnake();
        presentScene();
        SDL_Delay(1000 / FPS);
    }
}
