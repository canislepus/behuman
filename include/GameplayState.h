#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "GameState.h"
#include "game.h"
#include "Player.h"

class GameplayState : public GameState
{
    public:
        GameplayState(Game* parent);
        virtual ~GameplayState();

        void keyDown(SDL_Event event);
        void keyUp(SDL_Event event);
        void update(double delta);

    protected:
        Player* player;
    private:
        //Key down flags
        bool k_up, k_down, k_left, k_right;
};

#endif // GAMEPLAYSTATE_H
