#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"


class Bullet : public Entity
{
    public:
        Bullet(GameState* parent, float x, float y, unsigned int team);
        void update(double delta);
        void onCollision(Entity e, double delta);

        //Damage inflicted on collision
        float damage;
        //Status effects inflicted on collision
        long long status_damage;
    protected:
    private:
};

#endif // BULLET_H
