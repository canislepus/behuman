#include "Player.h"
#include "GameState.h"
#include <iostream>

using namespace std;

Player::Player(GameState* parent, float x, float y) : Entity(parent, x, y)
{
    this->texture = parent->getTexture(3);
    setDimensions(20, 20);
}

Player::~Player()
{
    //dtor
}


void Player::update(double delta)
{
    Entity::update(delta);
    //cout << this->vx << " | " << this->vy << endl;
}

void Player::onCollision(Entity e, double delta){
    x -= vx * delta;
    y -= vy * delta;
    centerX = x + w / 2;
    centerY = y + h / 2;
    collider->translate(-vx * delta, -vy * delta);
    //cout << "Collision detected." << endl;
}
