void initApple() {
    apple = malloc(sizeof(Apple));
    memset(apple, 0, sizeof(Apple));
    apple->x = 200;
    apple->y = 400;
    apple->w = WIDTH;
    apple->h = HEIGHT;
    apple->texture = textures.apple;
}

void showScore() {
	TTF_Font *font = TTF_OpenFont("arial.ttf", 20);
	SDL_Texture *scoreTexture = NULL;
	SDL_Rect scoreRect;
	char string[64] = "SCORE: ";
	char num[64];
	sprintf(num, "%d", score);
	strcat(string, num);
	scoreRect.x = SCREEN_WIDTH / 2 - 50;
	scoreRect.y = 10;
	scoreRect.w = 50;
	scoreRect.h = 20;
	makeButton(app.renderer, scoreRect.x, scoreRect.y, string, &scoreTexture, &scoreRect, font);
	drawButton(scoreTexture, &scoreRect);
}

int snakeEat(Snake *obj1, Apple *obj2) {
    if (obj1->x + obj1->w > obj2->x &&
        obj1->x < obj2->w + obj2->x &&
        obj1->y + obj1->h > obj2->y &&
        obj1->y < obj2->h + obj2->y)
        return 1;
    else
        return 0;
}

void genApplePos(){
    time_t t;
    
    srand((unsigned) time(&t));
    int overlap = 1;
    while (overlap){
        apple->x = rand() % SCREEN_WIDTH - WIDTH;
        apple->y = rand() % SCREEN_HEIGHT - HEIGHT;
        if(apple->x < 0 + WIDTH || apple->y < 0 + HEIGHT)
            continue;
        for(Snake *ptr = snake; ptr != NULL; ptr = ptr->next){
            if(snakeEat(ptr, apple))
                break;
            overlap = 0;
        }
    }
        
}

void scoreUpdate(){
    score += 5;
}

void appleEaten(){
    if(snakeEat(snake, apple)){
        genApplePos();
        pushTail();
        scoreUpdate();
    }
}

void drawApple() {
    appleEaten();
    blit(apple->texture, apple->x, apple->y, 25, 25, 0);
}
