void appendNode(Snake **snake, int x, int y, int w, int h, double angle, int dx, int dy, int turn, SDL_Texture *tex) {
    Snake *new = malloc(sizeof(Snake));
    Snake *last = *snake;
    new->x = x;
    new->y = y;
    new->w = w;
    new->h = h;
    new->angle = angle;
    new->dx = dx;
    new->dy = dy;
    new->turn = turn;
    new->texture = tex;
    new->next = NULL;
    if(*snake == NULL) {
        new->prev = NULL;
        *snake = new;
        return;
    }
    while(last->next != NULL)
        last = last->next;

    last->next = new;
    new->prev = last;
}

void pushTail(){
    Snake *last = snake;
    while(last->next != NULL)
        last = last->next;
    last->texture = textures.body;;
    appendNode(&snake, last->x, last->y, 21, HEIGHT, last->angle, 0, 1, 0, textures.tail);
}

void freeSnake() {
    Snake *head = snake;
    Snake *tmp = NULL;
    while(head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    snake = NULL;
}

void freeTurns() {
    Snake *head = turns;
    Snake *tmp = NULL;
    while(head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    turns = NULL;
}

void initSnake() {
    freeSnake();
    freeTurns();
    score = 0;
    appendNode(&snake, 100, 200, WIDTH, HEIGHT, 0, 0, 1, 0, textures.head);
    appendNode(&snake, 100, 173, 21, HEIGHT, 0, 0, 1, 0, textures.tail);
}

int overlap(Snake *obj1, Snake *obj2) {
    if (obj1->x + obj1->w > obj2->x &&
        obj1->x < obj2->w + obj2->x &&
        obj1->y + obj1->h > obj2->y &&
        obj1->y < obj2->h + obj2->y)
        return 1;
    else
        return 0;
}

void turn() {
    if(snake->next->next == NULL)
        return;
    if(snake->turn) {
    double angle;
        if(snake->angle == 90 && snake->next->next->angle == 180)
            angle = 180;
        else if(snake->angle == 90 && snake->next->next->angle == 0)
            angle = 270;
        else if(snake->angle == 270 && snake->next->next->angle == 180)
            angle = 90;
        else if(snake->angle == 270 && snake->next->next->angle == 0)
            angle = 0;
        else if(snake->angle == 0 && snake->next->next->angle == 90)
            angle = 90;
        else if(snake->angle == 0 && snake->next->next->angle == 270)
            angle = 180;
        else if(snake->angle == 180 && snake->next->next->angle == 90)
            angle = 0;
        else if(snake->angle == 180 && snake->next->next->angle == 270)
            angle = 270;
        appendNode(&turns, snake->next->x, snake->next->y, 22, 22, angle, 0, 0, 0, textures.turn);
        snake->turn = 0;
    }

    if(turns == NULL)
        return;

    Snake *tail = snake;
    while(tail->next != NULL)
        tail = tail->next;

    for(Snake *ptr = turns; ptr != NULL; ptr = ptr->next) {
        if(overlap(tail, ptr)){
            if(turns->next == NULL) {
                free(turns);
                turns = NULL;
            }else {
            turns = turns->next;
            free(turns->prev);
            }
        }
    }
}

void move() {
    for(Snake *ptr = snake->next; ptr != NULL; ptr = ptr->next) {
        if(overlap(snake, ptr)) {
            initSnake();
            menuClose = 0;
        }
    }

    Snake *last = snake;
    while(last->next != NULL)
        last = last->next;

    for(Snake *ptr = last; ptr != NULL; ptr = ptr->prev) {
        if(ptr->prev == NULL){
            if(ptr->x < 0)
                ptr->x = SCREEN_WIDTH;
            else if(ptr->y < 0)
                ptr->y = SCREEN_HEIGHT;
            else if(ptr->x > SCREEN_WIDTH - WIDTH)
                ptr->x = 0 - WIDTH;
            else if(ptr->y > SCREEN_HEIGHT - 5)
                ptr->y = 0;
            ptr->x += WIDTH * ptr->dx;
            ptr->y += HEIGHT * ptr->dy;
            break;
        }
        ptr->x = ptr->prev->x;
        ptr->y = ptr->prev->y;
        ptr->angle = ptr->prev->angle;
    }
    ++moved;
    turn();
}

void drawSnake() {
    for(Snake *ptr = snake; ptr != NULL; ptr = ptr->next){
        int noBody = 0;
        for(Snake *check = turns; check != NULL; check = check->next) {
            if(overlap(ptr, check))
                noBody = 1;
        }
        if(noBody)
            continue;
        if(ptr->prev == NULL){
            blit(ptr->texture, ptr->x, ptr->y, 30, 30, ptr->angle);
            continue;
        }
        blit(ptr->texture, ptr->x+6, ptr->y, 18, 30, ptr->angle);
    }
    for(Snake *ptr = turns; ptr != NULL; ptr = ptr->next) {
        blit(ptr->texture, ptr->x+4, ptr->y+4, ptr->w, ptr->h, ptr->angle);
    }
}
