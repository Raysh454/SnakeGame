void doKeyDown(SDL_KeyboardEvent *event) {
    if(moved == 0)
        return;
    if(event->repeat == 0) {
        if(event->keysym.scancode == SDL_SCANCODE_UP && snake->dy != 1) {
            if(snake->dy != 1 && snake->dx != 0)
                snake->turn = 1;
            snake->dy = -1;
            snake->dx = 0;
            snake->angle = 180;
            moved = 0;
        }
        if(event->keysym.scancode == SDL_SCANCODE_DOWN && snake->dy != -1) {
            if(snake->dy != 1 && snake->dx != 0)
                snake->turn = 1;
            snake->dy = 1;
            snake->dx = 0;
            snake->angle = 0;
            moved = 0;
        }
        if(event->keysym.scancode == SDL_SCANCODE_LEFT && snake->dx != 1) {
            if(snake->dy != 0 && snake->dx != -1)
                snake->turn = 1;
            snake->dy = 0;
            snake->dx = -1;
            snake->angle = 90;
            moved = 0;
        }
        if(event->keysym.scancode == SDL_SCANCODE_RIGHT && snake->dx != -1) {
            if(snake->dy != 0 && snake->dx != 1)
                snake->turn = 1;
            snake->dy = 0;
            snake->dx = 1;
            snake->angle = 270;
            moved = 0;
        }
        if(event->keysym.scancode == SDL_SCANCODE_ESCAPE){
            if(!menuClose)
                menuClose = 1;
            else
                menuClose = 0;
        }

        
    }
}

int buttonClick(int mouseX, int mouseY, SDL_Rect button) {
    if(mouseY >= button.y &&
        mouseY <= button.y + button.h &&
        mouseX >= button.x &&
        mouseX <= button.x + button.w)
            return 1;
        else
            return 0;
}

void doMouseEvent(SDL_MouseButtonEvent *event) {
    if(event->button == SDL_BUTTON_LEFT){
        if(buttonClick(mouse.x, mouse.y, buttons.play))
            menuClose = 1;
        else if(buttonClick(mouse.x, mouse.y, buttons.quit))
        	exit(0);
    }
}


void input() {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch(event.type)
        {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                doKeyDown(&event.key);
                break;
            case SDL_MOUSEBUTTONDOWN:
                doMouseEvent(&event.button);
            default:
                break;
        }
    }
}
