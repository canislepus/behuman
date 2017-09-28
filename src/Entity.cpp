#include "Entity.h"
#include "GameState.h"
#include <iostream>

#define toDegrees 57.295779513
#define toRadians 0.017453293

Entity::Entity(GameState* parent, float x, float y)
{
    this->parent = parent;
    this->x = x;
    this->y = y;

    //default dimensions
    this->w = 20;
    this->h = 20;

    centerX = x + w / 2;
    centerY = y + h / 2;

    angle = 0.0;
    displayAngle = 0;
    uaad = true;

    collidable = true;

    animCols = 1;
    animRows = 1;
    animRect.x = 0;
    animRect.y = 0;
    animRect.w = 1;
    animRect.h = 1;
    animDelay = 99999999;

    collider = new BoundingRect(centerX, centerY, w, h, angle);
}

Entity::~Entity()
{
    //dtor
}


void Entity::update(double delta)
{
    x += vx * delta;
    y += vy * delta;

    //centerX += vx * delta;
    //centerY += vy * delta;
    centerX = x + w / 2;
    centerY = y + h / 2;

    angle += va * delta;

    collider->translate(vx * delta, vy * delta);
  //  collider->rotate(va * delta);
}


void Entity::doAnimation(double delta)
{
    if(animDelay_left <= 0){
        animX = (animX + 1) % animCols;
        animRect.x = animX / animCols;
        animDelay_left = animDelay;
    }

    animDelay_left -= delta;
}


float Entity::getSpeed()
{
    return v;
}


void Entity::setSpeed(float speed)
{
    v = speed;
    vx = v * cos(angle * toRadians);
    vy = v * sin(angle * toRadians);
}


float Entity::getAngle()
{
    return angle;
}


void Entity::setAngle(float theta)
{
    //cout << "Set angle to " << theta << endl;
    angle = theta;
    vx = v * cos(angle * toRadians);
    vy = v * sin(angle * toRadians);

    collider->setAngle(angle);
}


void Entity::setDimensions(float w, float h)
{
    this->w = w;
    this->h = h;

    centerX = x + w / 2;
    centerY = y + h / 2;

    //cout << 1 << endl;
    collider->recalculate(centerX, centerY, w, h, angle);
    //cout << 2 << endl;
}


void Entity::useAngleForDisplay(bool b){
    uaad = b;
}


void Entity::prepareAnimation(int rows, int cols, long int delay)
{
    animRows = rows;
    animCols = cols;
    animX = 0;
    animY = 0;
    animRect.w = 1 / cols;
    animRect.h = 1 / rows;
    animDelay = delay;
    animDelay_left = delay;
}
