#include "game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>
#include "ImageLoader.h"

using namespace std;

Game::Game(SDL_Window *win, SDL_Renderer *ren)
{
    this->win = win;
    this->ren = ren;

    this->textures = loadImages(ren);

    currentState = NULL;

    paused = false;
    exit = false;
}


void Game::run()
{
    previousTime = SDL_GetTicks();
    while(!exit){
        currentTime = SDL_GetTicks();
        double delta = currentTime - previousTime;
        handleEvents();
        update(delta);
        currentState->checkForCollisions(delta);
        render(delta);

        previousTime = currentTime;
    }

    quit();
}


void Game::update(double delta)
{
    //cout << "update" << endl;
    currentState->update(delta);
    //cout << "update finished" << endl;
}


void Game::render(double delta)
{
    //cout << "render" << endl;
    SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(ren);
    currentState->render(ren, delta);
    SDL_RenderPresent(ren);
    //cout << "render finished" << endl;
}


void Game::handleEvents()
{
    mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            exit = true;
        }
        else if(event.type == SDL_KEYDOWN){
            currentState->keyDown(event);
        }
        else if(event.type == SDL_KEYUP){
            currentState->keyUp(event);
        }
    }
}


void Game::setState(GameState* state){
    currentState = state;
}


void Game::quit()
{
    for(SDL_Texture *tex : textures)
        SDL_DestroyTexture(tex);

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
}
