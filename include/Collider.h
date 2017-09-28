#ifndef COLLIDER_H
#define COLLIDER_H
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

using namespace glm;


enum ColliderType {CIRCLE, RECTANGLE};

class Collider {
public:
    ColliderType type;

    virtual void recalculate(float x, float y, float w, float h, float angle){}
    virtual void translate(float dx, float dy){}
    virtual void setPos(float x, float y){}
    virtual void resize(float w, float h){}
    virtual void rotate(float angle){}
    virtual void setAngle(float angle){}

};


class BoundingCircle : public Collider {
public:
    //const static ColliderType type = CIRCLE;
    vec2 pos;
    float radius;

    BoundingCircle(float x, float y, float r, float angle);
    void recalculate(float x, float y, float r, float angle);
    void recalculate(float x, float y, float w, float h, float angle);
    void translate(float dx, float dy);
    void setPos(float x, float y);
    void resize(float w, float h);
};


class BoundingRect : public Collider {
public:
    //const static ColliderType type = RECTANGLE;

    vec2 pos;
    vec2 dimensions;
    float angle;

    vec2 vertices[4];

    BoundingRect(float x, float y, float w, float h, float angle);
    void recalculate(float x, float y, float w, float h, float angle);
    void translate(float dx, float dy);
    void setPos(float x, float y);
    void resize(float w, float h);
    void rotate(float angle);
    void setAngle(float angle);

};


mat2 getRotationMatrix(float theta);
bool checkCollision(BoundingRect* a, BoundingRect* b);
bool checkCollision(BoundingCircle* a, BoundingCircle* b);
bool checkCollision(BoundingCircle* a, BoundingRect* b);
bool checkCollision(Collider* a, Collider* b);


#endif // COLLIDER_H
