#include "GameState.h"
#include "game.h"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

GameState::GameState(Game* parent)
{
    this->parent = parent;
}


//Dummy constructor just to prevent compiler errors.
//DON'T CALL!
GameState::GameState()
{
    parent = NULL;
}


GameState::~GameState()
{

}


void GameState::render(SDL_Renderer* ren, double delta)
{
    SDL_Rect entrect;

        entrect.x = 0;
        entrect.y = 0;

    for(Entity* ent : entities){
        //cout << "doAnimation" << endl;

        ent->doAnimation(delta);
        //cout << "doAnimation finished" << endl;
        entrect.x = -ent->w / 2;
        entrect.y = -ent->h / 2;
        entrect.w = ent->w;
        entrect.h = ent->h;
        //cout << ent->animRect.x << " " << ent->animRect.y << " " << ent->animRect.w << " " << ent->animRect.h << " " << endl;
        glTranslatef(ent->centerX, ent->centerY, 0);
        glRotatef(ent->getAngle(), 0, 0, 1);
        SDL_RenderCopy(ren, ent->texture, &(ent->animRect), &entrect);
        glRotatef(-ent->getAngle(), 0, 0, 1);
        glTranslatef(-ent->centerX, -ent->centerY, 0);

        //*
        //Render collision boxes for debugging
        if(ent->collider->type == RECTANGLE){
            BoundingRect* br = (BoundingRect*) ent->collider;
            SDL_Point points[5];
            for(int i = 0; i < 5; i++){
                points[i].x = br->vertices[i % 4].x;
                points[i].y = br->vertices[i % 4].y;
            }
            SDL_SetRenderDrawColor(ren, 255, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawLines(ren, points, 5);
        }
        /**/
    }
}


void GameState::update(double delta)
{
    for(Entity* ent : entities){
        ent->update(delta);
    }
}


void GameState::checkForCollisions(double delta)
{

    for(unsigned int i = 0; i < entities.size() - 1; i++){
        if(!entities.at(i)->collidable)
            continue;
        Entity* a = entities.at(i);
        for(unsigned int n = i + 1; n < entities.size(); n++){           //Nested loop so that every sprite is only checked with the sprites after it and not just every sprite.

            if(!entities.at(n)->collidable)
                continue;
            Entity* b = entities.at(n);

            if(checkCollision(&*a->collider, &*b->collider)){
                a->onCollision(*b, delta);
                b->onCollision(*a, delta);
            }
        }
    }
}


void GameState::keyDown(SDL_Event event)
{

}


void GameState::keyUp(SDL_Event event)
{

}


void GameState::addEntity(Entity* ent)
{
    entities.push_back(ent);
}


SDL_Texture* GameState::getTexture(unsigned int key)
{
    if(key >= parent->textures.size())
        return NULL;

    return parent->textures.at(key);
}
