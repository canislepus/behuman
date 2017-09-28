#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include "Collider.h"

class GameState;

class Entity
{
    public:
        Entity(GameState* parent, float x, float y);
        virtual ~Entity();
        virtual void update(double delta);
        void draw(SDL_Renderer* ren);
        void doAnimation(double delta);
        void applyTransformations();

        virtual void onCollision(Entity e, double delta){}

        float getSpeed();
        void setSpeed(float speed);
        float getAngle();
        void setAngle(float theta);
        void useAngleForDisplay(bool b);
        void setDimensions(float w, float h);

        GameState* parent;

        //Position
        float x, y;
        //Dimensions
        float w, h;

        bool collidable;
        Collider* collider;



        SDL_Texture* texture;

        //Rectangle around the current animation frame.
        //Do not worry about this too much. It is updated automatically each frame.
        SDL_Rect animRect;

        float centerX, centerY;

    protected:

        //Velocity.
        float v;

        //Velocity components. Set automatically when calling either setSpeed or setAngle.
        float vx, vy;

        //Movement angle
        float angle;

        //Angle of the texture displayed on screen
        float displayAngle;

        //Use Angle As Display angle
        bool uaad;

        //Changing rate of the angle
        float va;



        //Number of rows and columns of the entity's sprite sheet
        unsigned int animRows, animCols;
        //Current position of the animation. animX is updated automatically as consecutive frames.
        //animY must be set manually for it represents different animation lines.
        unsigned int animX, animY;
        //Delay between animation frames. animDelay_left marks how much of the delay is left for the current frame
        //and it should not be necessary to change it manually. It is decremented by delta every frame.
        long int animDelay, animDelay_left;

        void prepareAnimation(int rows, int cols, long int delay);
    private:
};

#endif // ENTITY_H
