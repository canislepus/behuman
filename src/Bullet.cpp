#include "Bullet.h"
#include "GameState.h"
#include <iostream>

using namespace std;

Bullet::Bullet(GameState* parent, float x, float y) : Entity(parent, x, y)
{
    texture = parent->getTexture(4);
    setDimensions(10, 10);
    setAngle(0);
}

void Bullet::update(double delta){
    Entity::update(delta);
    //cout << angle << endl;
}


void Bullet::onCollision(Entity e, double delta){
    if(e == parent)
        return;


}