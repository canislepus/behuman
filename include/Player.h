#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"


class Player : public Entity
{
    public:
        Player(GameState* parent, float x, float y);
        virtual ~Player();

        void update(double delta);
        void onCollision(Entity e, double delta);
    protected:
    private:
};

#endif // PLAYER_H
