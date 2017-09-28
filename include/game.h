#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <vector>
#include <SDL.h>

#include "GameState.h"


class Game{
public:
    Game(SDL_Window*, SDL_Renderer*);
    void run();
    void update(double delta);
    void render(double delta);
    void handleEvents();
    void quit();

    void setState(GameState* state);

    std::vector<SDL_Texture*> textures;
    int mouseX, mouseY;
    unsigned int mouseState;

private:
    SDL_Window *win;
    SDL_Renderer *ren;

    GameState* currentState;
    bool paused;
    bool exit;

    double currentTime;
    double previousTime;



};

#endif // GAME_H_INCLUDED
