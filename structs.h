typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

typedef struct {
    int x;
    int y;
} mousePos;

typedef struct Snake{
    int x;
    int y;
    int w;
    int h;
    double angle;
    int dx;
    int dy;
    int turn;
    SDL_Texture *texture;
    struct Snake *next;
    struct Snake *prev;
} Snake;

typedef struct {
    int x;
    int y;
    int w;
    int h;
    SDL_Texture *texture;
} Apple;

typedef struct {
    SDL_Texture *head;
    SDL_Texture *body;
    SDL_Texture *tail;
    SDL_Texture *turn;
    SDL_Texture *apple;
} Textures;

typedef struct {
	SDL_Rect title;
    SDL_Rect play;
    SDL_Rect score;
    SDL_Rect quit;
} Buttons;

mousePos mouse;
App app;
Textures textures;
Apple *apple = NULL;
Snake *snake = NULL;
Snake *turns = NULL;
Buttons buttons;
