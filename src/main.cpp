
#include <cstdlib>
#include <iostream>
#include <vector>
#include <SDL.h>

#include "ImageLoader.h"
#include "game.h"
#include "GameplayState.h"
#include "Player.h"

#include "tests/tests.h"
//#define TEST

using namespace std;

inline void render(SDL_Window*, SDL_Renderer*);

int main ( int argc, char** argv )
{

    #ifdef TEST
        performTests();
        return 0;
    #endif


    if (SDL_Init(SDL_INIT_VIDEO) != 0){
		cerr << "SDL_Init Error: " << SDL_GetError() << endl;
		return 1;
    }

    initImageLoader();

    // create a new window
    SDL_Window *screen = SDL_CreateWindow("Be Human", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
    if(screen == nullptr){
     cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
     SDL_Quit();
     return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr){
     cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
     SDL_DestroyWindow(screen);
     SDL_Quit();
     return 1;
    }

    SDL_RenderSetLogicalSize(renderer, 1920, 1080);



    Game* game = new Game(screen, renderer);
    GameplayState* playstate = new GameplayState(game);
    //playstate->addEntity(new Player(playstate, 0, 0));
    game->setState(playstate);
    game->run();
    game->quit();


    return 0;
}
