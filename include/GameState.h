#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL.h>
#include <vector>

//#include "game.h"
#include "Entity.h"

using namespace std;

class Game;

class GameState
{
    public:
        GameState(Game* parent);
        GameState();
        ~GameState();
        virtual void update(double delta);
        void checkForCollisions(double delta);
        virtual void render(SDL_Renderer* ren, double delta);

        virtual void keyDown(SDL_Event event);
        virtual void keyUp(SDL_Event event);

        void addEntity(Entity* ent);
        SDL_Texture* getTexture(unsigned int key);

        vector<Entity*> entities;
        int mouseX, mouseY;


    protected:
        Game* parent;

    private:
};

#endif // GAMESTATE_H
