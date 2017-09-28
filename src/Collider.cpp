#include "Collider.h"

#include <iostream>

#define toRadians 0.017453293f
//#define project(v, s) (dot((dot(v, s) / dot(s, s)) * s , s))
#define project(v, s) (dot(v, s))

using namespace glm;


BoundingCircle::BoundingCircle(float x, float y, float r, float angle)
{
    type = CIRCLE;
    pos.x = x;
    pos.y = y;
    radius = r;
}


void BoundingCircle::recalculate(float x, float y, float r, float angle)
{
    pos.x = x;
    pos.y = y;
    radius = r;
}


void BoundingCircle::recalculate(float x, float y, float w, float h, float angle)
{
    pos.x = x;
    pos.y = y;
    radius = (w + h) / 4;
}


void BoundingCircle::translate(float dx, float dy)
{
    pos.x += dx;
    pos.y += dy;
}


void BoundingCircle::setPos(float x, float y)
{
    pos.x = x;
    pos.y = y;
}


void BoundingCircle::resize(float w, float h)
{
    radius = (w + h) / 2;
}


////////////////////////////////////BoundingRect////////////////////////////////////////////////////////////////////////


BoundingRect::BoundingRect(float x, float y, float w, float h, float angle)
{
    type = RECTANGLE;
    //Set position and dimensions
    pos.x = x;
    pos.y = y;
    dimensions.x = w;
    dimensions.y = h;
    this->angle = fmod(angle, 90);

    //set position of vertices
    vertices[0].x = -w / 2;
    vertices[0].y = -h / 2;
    vertices[1].x = w / 2;
    vertices[1].y = -h / 2;
    vertices[2].x = w / 2;
    vertices[2].y = h / 2;
    vertices[3].x = -w / 2;
    vertices[3].y = h / 2;



//*    //Rotate it
    mat2 rotmat = getRotationMatrix(this->angle);

    vertices[0] = rotmat * vertices[0];
    vertices[1] = rotmat * vertices[1];
    vertices[2] = rotmat * vertices[2];
    vertices[3] = rotmat * vertices[3];

    vertices[0].x += x;
    vertices[0].y += y;
    vertices[1].x += x;
    vertices[1].y += y;
    vertices[2].x += x;
    vertices[2].y += y;
    vertices[3].x += x;
    vertices[3].y += y;

/*
for(int i = 0; i <= 3; i++){
        std::cout << vertices[i].x << " | " << vertices[i].y << std::endl;
    }
/**/
}


void BoundingRect::recalculate(float x, float y, float w, float h, float angle)
{
    //Set position and dimensions
    pos.x = x;
    pos.y = y;
    dimensions.x = w;
    dimensions.y = h;
    this->angle = fmod(angle, 90);

    //set position of vertices relative to origin
    vertices[0].x = -w / 2;
    vertices[0].y = -h / 2;
    vertices[1].x = w / 2;
    vertices[1].y = -h / 2;
    vertices[2].x = w / 2;
    vertices[2].y = h / 2;
    vertices[3].x = -w / 2;
    vertices[3].y = h / 2;

    //Rotate it
    mat2 rotmat = getRotationMatrix(this->angle);

    vertices[0] = rotmat * vertices[0];
    vertices[1] = rotmat * vertices[1];
    vertices[2] = rotmat * vertices[2];
    vertices[3] = rotmat * vertices[3];

    //Translate it
    vertices[0].x += x;
    vertices[0].y += y;
    vertices[1].x += x;
    vertices[1].y += y;
    vertices[2].x += x;
    vertices[2].y += y;
    vertices[3].x += x;
    vertices[3].y += y;

}


void BoundingRect::translate(float dx, float dy)
{
    pos.x += dx;
    pos.y += dy;

    for(vec2 vertex : vertices){
        vertex.x += dx;
        vertex.y += dy;
    }
}


void BoundingRect::setPos(float x, float y)
{
    pos.x = x;
    pos.y = y;

    vertices[0].x = -dimensions.x / 2;
    vertices[0].y = -dimensions.y / 2;
    vertices[1].x = dimensions.x / 2;
    vertices[1].y = -dimensions.y / 2;
    vertices[2].x = dimensions.x / 2;
    vertices[2].y = dimensions.y / 2;
    vertices[3].x = -dimensions.x / 2;
    vertices[3].y = dimensions.y / 2;


    mat2 rotmat = getRotationMatrix(this->angle);

    vertices[0] = rotmat * vertices[0];
    vertices[1] = rotmat * vertices[1];
    vertices[2] = rotmat * vertices[2];
    vertices[3] = rotmat * vertices[3];

    vertices[0].x += x;
    vertices[0].y += y;
    vertices[1].x += x;
    vertices[1].y += y;
    vertices[2].x += x;
    vertices[2].y += y;
    vertices[3].x += x;
    vertices[3].y += y;

}


void BoundingRect::resize(float w, float h)
{
    dimensions.x = w;
    dimensions.y = h;

    vertices[0].x = -w / 2;
    vertices[0].y = -h / 2;
    vertices[1].x = w / 2;
    vertices[1].y = -h / 2;
    vertices[2].x = w / 2;
    vertices[2].y = h / 2;
    vertices[3].x = -w / 2;
    vertices[3].y = h / 2;

    //Rotate it
    mat2 rotmat = getRotationMatrix(this->angle);

    vertices[0] = rotmat * vertices[0];
    vertices[1] = rotmat * vertices[1];
    vertices[2] = rotmat * vertices[2];
    vertices[3] = rotmat * vertices[3];

    //Translate it
    vertices[0].x += pos.x;
    vertices[0].y += pos.y;
    vertices[1].x += pos.x;
    vertices[1].y += pos.y;
    vertices[2].x += pos.x;
    vertices[2].y += pos.y;
    vertices[3].x += pos.x;
    vertices[3].y += pos.y;
}


void BoundingRect::rotate(float angle)
{
    this->angle = fmod(this->angle + angle, 90);

//*
    //Translate to origin for proper pivot point
    vertices[0].x -= pos.x;
    vertices[0].y -= pos.y;
    vertices[1].x -= pos.x;
    vertices[1].y -= pos.y;
    vertices[2].x -= pos.x;
    vertices[2].y -= pos.y;
    vertices[3].x -= pos.x;
    vertices[3].y -= pos.y;
/**/

/*
    vertices[0].x = -dimensions.x / 2;
    vertices[0].y = -dimensions.y / 2;
    vertices[1].x = dimensions.x / 2;
    vertices[1].y = -dimensions.y / 2;
    vertices[2].x = dimensions.x / 2;
    vertices[2].y = dimensions.y / 2;
    vertices[3].x = -dimensions.x / 2;
    vertices[3].y = dimensions.y / 2;
/**/

    mat2 rotmat = getRotationMatrix(this->angle);

    vertices[0] = rotmat * vertices[0];
    vertices[1] = rotmat * vertices[1];
    vertices[2] = rotmat * vertices[2];
    vertices[3] = rotmat * vertices[3];

    //Translate back
    vertices[0].x += pos.x;
    vertices[0].y += pos.y;
    vertices[1].x += pos.x;
    vertices[1].y += pos.y;
    vertices[2].x += pos.x;
    vertices[2].y += pos.y;
    vertices[3].x += pos.x;
    vertices[3].y += pos.y;
}


void BoundingRect::setAngle(float angle)
{
    this->angle = fmod(angle, 90);

    vertices[0].x = -dimensions.x / 2;
    vertices[0].y = -dimensions.y / 2;
    vertices[1].x = dimensions.x / 2;
    vertices[1].y = -dimensions.y / 2;
    vertices[2].x = dimensions.x / 2;
    vertices[2].y = dimensions.y / 2;
    vertices[3].x = -dimensions.x / 2;
    vertices[3].y = dimensions.y / 2;

    //Rotate it
    mat2 rotmat = getRotationMatrix(this->angle);

    vertices[0] = rotmat * vertices[0];
    vertices[1] = rotmat * vertices[1];
    vertices[2] = rotmat * vertices[2];
    vertices[3] = rotmat * vertices[3];

    //Translate it
    vertices[0].x += pos.x;
    vertices[0].y += pos.y;
    vertices[1].x += pos.x;
    vertices[1].y += pos.y;
    vertices[2].x += pos.x;
    vertices[2].y += pos.y;
    vertices[3].x += pos.x;
    vertices[3].y += pos.y;

}


//////////////////////////////////////Collision checking/////////////////////////////////////////

bool checkCollision(Collider* a, Collider* b)
{
    if(a == nullptr || b == nullptr)
        return false;
/*
    std::cout << RECTANGLE << std::endl;
    std::cout << "a: " << a.type << "\nb: " << b.type << std::endl;
    std::cout << (static_cast<BoundingRect*>(&a)) << std::endl;
/**/
    if(a->type == RECTANGLE){
        if(b->type == RECTANGLE)
            return checkCollision((BoundingRect*) a, (BoundingRect*) b);

        return checkCollision((BoundingCircle*) a, (BoundingRect*) b);
    }

    if(b->type == RECTANGLE)
        return checkCollision((BoundingCircle*) a, (BoundingRect*) b);

    return checkCollision((BoundingCircle*) a, (BoundingCircle*) b);
}


bool checkCollision(BoundingCircle* a, BoundingCircle* b)
{
    return length(a->pos - b->pos) <= a->radius + b->radius;
}


bool checkCollision(BoundingCircle* a, BoundingRect* b)
{
    vec2 temppos = getRotationMatrix(-b->angle) * (a->pos - b->pos);

    /*
    std::cout << "angle: "  << b->angle;
    std::cout << "radius: " << a->radius << std::endl;
    std::cout << a->pos.x << " | " << a->pos.y << std::endl;
    std::cout << "tmppos: " << temppos.x << " | " << temppos.y << std::endl;
    for(int i = 0; i <= 3; i++){
        std::cout << b->vertices[i].x << " | " << b->vertices[i].y << std::endl;
    }
    /**/

    if(temppos.x + a->radius < -b->dimensions.x / 2 || temppos.x - a->radius > b->dimensions.x / 2 || temppos.y + a->radius < -b->dimensions.y / 2 || temppos.y -a->radius > b->dimensions.y / 2)
        return false;

    return true;
}


bool checkCollision(BoundingRect* a, BoundingRect* b)
{

/*
    for(int i = 0; i <= 3; i++){
        std::cout << a->vertices[i].x << " | " << a->vertices[i].y << std::endl;
    }

    for(int i = 0; i <= 3; i++){
        std::cout << b->vertices[i].x << " | " << b->vertices[i].y << std::endl;
    }
/**/

    //Axes for first rect
    vec2 axis1 = a->vertices[1] - a->vertices[0];             //Equivalent of x axis
    vec2 axis2 = a->vertices[2] - a->vertices[1];              //Equivalent of y axis

/*
    std::cout << "axis1 = ( " << axis1.x << " | " << axis1.y << " )" << std::endl;
    std::cout << "axis2 = ( " << axis2.x << " | " << axis2.y << " )" << std::endl;
/**/

//*
    //Maximum and minimum on axis1
    float max1 = project(a->vertices[1], axis1);
    float min1 = project(a->vertices[0], axis1);

    //Same for axis2
    float max2 = project(a->vertices[2], axis2);
    float min2 = project(a->vertices[1], axis2);
/**/

    //Calculate the maximum for the second rectangle
    //float bmax1 = project(b->vertices[0], axis1);
    int i = 0;
    i = (project(b->vertices[1], axis1) > project(b->vertices[i], axis1)) ? 1 : i;
    i = (project(b->vertices[2], axis1) > project(b->vertices[i], axis1)) ? 2 : i;
    i = (project(b->vertices[3], axis1) > project(b->vertices[i], axis1)) ? 3 : i;
    float bmax1 = project(b->vertices[i], axis1);
    //The minimum is automatically the vertex opposite to the maximum.
    float bmin1 = project(b->vertices[(i + 2) % 4], axis1);

    //Because it is a rectangle and clockwise, the extrema on axis2 must be as follows:
    float bmax2 = project(b->vertices[(i + 1) % 4], axis2);
    float bmin2 = project(b->vertices[(i - 1) % 4], axis2);

/*
if(a->angle == 180 || b->angle == 180){
    std::cout << std::endl;
    std::cout << "a->angle: " << a->angle << std::endl;
    std::cout << "b->angle: " << b->angle << std::endl;
    std::cout << "min1: " << min1 << " | max1: " << max1 << std::endl;
    std::cout << "bmin1: " << bmin1 << " | bmax1: " << bmax1 << std::endl;
    std::cout << "min2: " << min2 << " | max2: " << max2 << std::endl;
    std::cout << "bmin2: " << bmin2 << " | bmax2: " << bmax2 << std::endl;
}
/**/

    //If there is any separation here, there can be no collision.
    if(bmin1 > max1 || bmax1 < min1 || bmin2 > max2 || bmax2 < min2)
        return false;
    //std::cout << "Check1 ";
    //std::cout << "a->angle: " << a->angle << "  b->angle: " << b->angle << std::endl;

    if(a->angle == b->angle)
        return true;

    //---------------------------------------------SECOND RECT-----------------------------

    //BoundingRect tmp = a;
    //a = b;
    //b = tmp;

    //Axes for second rect
    axis1 = b->vertices[1] - b->vertices[0];             //Equivalent of x axis
    axis2 = b->vertices[2] - b->vertices[1];             //Equivalent of y axis

/*
    std::cout << "baxis1 = ( " << axis1.x << " | " << axis1.y << " )" << std::endl;
    std::cout << "baxis2 = ( " << axis2.x << " | " << axis2.y << " )\n" << std::endl;
/**/

//*
    //Maximum and minimum on axis1
    max1 = project(b->vertices[1], axis1);
    min1 = project(b->vertices[0], axis1);

    //Same for axis2
    max2 = project(b->vertices[2], axis2);
    min2 = project(b->vertices[1], axis2);
/**/

    //Calculate the maximum for the second rectangle
    //bmax1 = project(a->vertices[0], axis1);
    i = 0;
    i = (project(a->vertices[1], axis1) > project(a->vertices[i], axis1)) ? 1 : i;
    i = (project(a->vertices[2], axis1) > project(a->vertices[i], axis1)) ? 2 : i;
    i = (project(a->vertices[3], axis1) > project(a->vertices[i], axis1)) ? 3 : i;
    bmax1 = project(a->vertices[i], axis1);
    //The minimum is automatically the vertex opposite to the maximum.
    bmin1 = project(a->vertices[(i + 2) % 4], axis1);

    //Because it is a rectangle and clockwise, the extrema on axis2 must be as follows:
    bmax2 = project(a->vertices[(i + 1) % 4], axis2);
    bmin2 = project(a->vertices[(i - 1) % 4], axis2);

/*
    if(a->angle == 180 || b->angle == 180){
    std::cout << "min1: " << min1 << " | max1: " << max1 << std::endl;
    std::cout << "bmin1: " << bmin1 << " | bmax1: " << bmax1 << std::endl;
    std::cout << "min2: " << min2 << " | max2: " << max2 << std::endl;
    std::cout << "bmin2: " << bmin2 << " | bmax2: " << bmax2 << std::endl;
    }
/**/

    //If there is any separation here, there can be no collision.
    if(bmin1 > max1 || bmax1 < min1 || bmin2 > max2 || bmax2 < min2)
        return false;
//    std::cout << "Check2" << std::endl;

    //If there is no separation, there is definitely a collision.
    return true;
}


/////////////////////////////////////Utility functions///////////////////////////////////////////

inline mat2 getRotationMatrix(float theta)
{
    mat2 m;
    float costheta = cos(theta * toRadians);
    float sintheta = sin(theta * toRadians);
    m[0].x = costheta;
    m[1].x = -sintheta;
    m[0].y = sintheta;
    m[1].y = costheta;
    return m;
}
