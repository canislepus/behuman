#include "GameplayState.h"
#include "Bullet.h"
#include <iostream>

#define PI 3.14159265358979323846
#define toDegrees 57.295779513
#define toRadians 0.017453293

using namespace std;

GameplayState::GameplayState(Game* parent) : GameState(parent)
{
    player = new Player(this, 320, 240);
    this->addEntity(player);
    //this->addEntity(new Bullet(this, 200, 300, TEAM_NEUTRAL));

    k_up = false;
    k_down = false;
    k_left = false;
    k_right = false;
}

GameplayState::~GameplayState()
{
    //dtor
}


void GameplayState::update(double delta)
{
    GameState::update(delta);
    player->setSpeed(0);

    if(k_down){

        if(k_left){
            player->setAngle(135);
        }else if(k_right){
            player->setAngle(45);
        }else{
            player->setAngle(90);
        }
        player->setSpeed(0.2);
    }
    else if(k_up){
        if(k_left){
            player->setAngle(225);
        }else if(k_right){
            player->setAngle(315);
        }else{
            player->setAngle(270);
        }
        player->setSpeed(0.2);
    }
    else if(k_left){
        player->setAngle(180);
        player->setSpeed(0.2);
    }
    else if(k_right){
        player->setAngle(0);
        player->setSpeed(0.2);
    }
}


void GameplayState::keyDown(SDL_Event event)
{
    SDL_Keycode key = event.key.keysym.sym;

    if(key == SDLK_UP){
        k_up = true;
    }
    else if(key == SDLK_DOWN){
        k_down = true;
    }
    else if(key == SDLK_LEFT){
        k_left = true;
    }
    else if(key == SDLK_RIGHT){
        k_right = true;
    }
}


void GameplayState::keyUp(SDL_Event event)
{
    SDL_Keycode key = event.key.keysym.sym;

    if(key == SDLK_UP){
        k_up = false;
    }
    else if(key == SDLK_DOWN){
        k_down = false;
    }
    else if(key == SDLK_LEFT){
        k_left = false;
    }
    else if(key == SDLK_RIGHT){
        k_right = false;
    }
}
