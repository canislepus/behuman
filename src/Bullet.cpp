#include "Bullet.h"
#include "GameState.h"
#include <iostream>

using namespace std;

Bullet::Bullet(GameState* parent, float x, float y, unsigned int team) : Entity(parent, x, y)
{
    texture = parent->getTexture(4);
    setDimensions(10, 10);
    setAngle(0);

    this->team = team;

    health = INFINITY;
}

void Bullet::update(double delta){
    Entity::update(delta);
    //cout << angle << endl;
}


void Bullet::onCollision(Entity e, double delta){
    if(e.team == team)
        return;

    e.health -= damage;
    e.status_effects |= status_damage;
    health = 0;
}
