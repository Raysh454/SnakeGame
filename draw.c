SDL_Texture *loadTexture(char *image) {
    SDL_Texture *texture;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading: %s", image);
    texture = IMG_LoadTexture(app.renderer, image);

    return texture;
}

void initTextures() {
    memset(&textures, 0, sizeof(Textures));
    textures.head = loadTexture("images/snake/head-small.png");
    textures.body = loadTexture("images/snake/body.png");
    textures.tail = loadTexture("images/snake/tail.png");
    textures.turn = loadTexture("images/snake/turn.png");
    textures.apple = loadTexture("images/snake/apple.png");
}


void blit(SDL_Texture *texture, int x, int y, int w, int h, double angle) {
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;

    SDL_RenderCopyEx(app.renderer, texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
}

void prepareScene() {
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
}

void presentScene() {
    SDL_RenderPresent(app.renderer);
}
