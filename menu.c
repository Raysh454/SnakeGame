static inline SDL_Color mk_SDL_Color(int r, int g, int b){
        SDL_Color const c = {r,g,b};
        return c;
    }

void makeButton(SDL_Renderer *renderer, int x, int y, char *text, SDL_Texture **texture, SDL_Rect *rect, TTF_Font *font) {
    int textHeight;
    int textWidth;
    SDL_Surface *surface;
    SDL_Color textColor = mk_SDL_Color(255,255,255);
    surface = TTF_RenderText_Blended(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    textWidth = surface->w;
    textHeight = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = textWidth;
    rect->h = textHeight;
}

void initMenuButtons(SDL_Texture **title, SDL_Texture **playButton, SDL_Texture **scoreButton, SDL_Texture **quitButton) {
	TTF_Font *font = TTF_OpenFont("arial.ttf", 40);
    buttons.title.y = 50;
    buttons.title.x = SCREEN_WIDTH/2 - 130;
    buttons.title.w = 50;
    buttons.title.h = 26;
    makeButton(app.renderer, buttons.title.x, buttons.title.y, "SNAKE GAME", title, &buttons.title, font);
    font = TTF_OpenFont("arial.ttf", 26);
    buttons.play.y = 250;
    buttons.play.x = SCREEN_WIDTH/2 - 40;
    buttons.play.w = 50;
    buttons.play.h = 26;
    makeButton(app.renderer, buttons.play.x, buttons.play.y, "Play", playButton, &buttons.play, font);
    buttons.score.y = 300;
    buttons.score.x = SCREEN_WIDTH/2 - 75;
    buttons.score.w = 50;
    buttons.score.h = 26;
    makeButton(app.renderer, buttons.score.x, buttons.score.y, "Highscore", scoreButton, &buttons.score, font);
    buttons.quit.y = 350;
    buttons.quit.x = SCREEN_WIDTH/2 - 40;
    buttons.quit.w = 50;
    buttons.quit.h = 26;
    makeButton(app.renderer, buttons.quit.x, buttons.quit.y, "Quit", quitButton, &buttons.quit, font);
    SDL_SetRenderDrawColor(app.renderer, 0, 100, 0, 255);
    SDL_RenderClear(app.renderer);
}

void drawButton(SDL_Texture *buttonTexture, SDL_Rect *button) {
    SDL_RenderCopy(app.renderer, buttonTexture, NULL, button);
}

void showScoreMenu() {
	
}

void menuLoop() {
    SDL_Texture *title = NULL, *playButton = NULL, *scoreButton = NULL, *quitButton = NULL;
    initMenuButtons(&title, &playButton, &scoreButton, &quitButton);
    drawButton(title, &buttons.title);
    drawButton(playButton, &buttons.play);
    drawButton(scoreButton, &buttons.score);
    drawButton(quitButton, &buttons.quit);
    presentScene();

    while(!menuClose) {
        SDL_GetMouseState(&mouse.x, &mouse.y);
        if(showHighScore == 1)
        	showScoreMenu();
        input();
    }
    SDL_DestroyTexture(title);
    SDL_DestroyTexture(playButton);
    SDL_DestroyTexture(scoreButton);
    SDL_DestroyTexture(quitButton);
}

void menu() {
    if(!menuClose)
        menuLoop();
}
