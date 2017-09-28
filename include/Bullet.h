#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"


class Bullet : public Entity
{
    public:
        Bullet(GameState* parent, float x, float y);
        void update(double delta);
        void onCollision(Entity e, double delta);
    protected:
    private:
};

#endif // BULLET_H
