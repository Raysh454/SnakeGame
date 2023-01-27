void cleanup(){
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_DestroyTexture(textures.head);
    SDL_DestroyTexture(textures.body);
    SDL_DestroyTexture(textures.tail);
    SDL_DestroyTexture(textures.turn);
    SDL_DestroyTexture(textures.apple);
    Snake *head = snake;
    Snake *tmp = NULL;
    while(head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    head = turns;
    tmp = NULL;
    while(head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    free(apple);
    TTF_Quit();
    SDL_Quit();
}
