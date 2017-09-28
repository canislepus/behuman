#include "tests.h"

#include <iostream>

#include "Collider.h"

using namespace std;

void assertTrue(string msg, bool b)
{
    cout << msg << (b ? " ...Passed" : " ...Failed") << endl;
}


void assertFalse(string msg, bool b)
{
    cout << msg << (!b ? " ...Passed" : " ...Failed") << endl;
}


void testCollisionRectRect()
{
    BoundingRect a(0.5, 1, 1, 1, 0);
    BoundingRect b(1.5, 1.5, 1, 1, 45);

    assertFalse("No collision if only one rect seems to be colliding", checkCollision(&a, &b));

    a.recalculate(0.5, 1, 1, 1, 45);
    assertFalse("...when both are parallel", checkCollision(&a, &b));

    a.recalculate(1.5, 1, 1, 1, 0);
    assertTrue("Collision when one rect is rotated", checkCollision(&a, &b));

    b.recalculate(2.5, 1, 1, 1, 0);
    assertTrue("Collision between two just touching rects", checkCollision(&a, &b));

    b.recalculate(1.5, 1, 1, 1, 0);
    assertTrue("Collision between two identical non-rotated rects", checkCollision(&a, &b));

    a.rotate(45);
    assertTrue("Collision with same position and different angles", checkCollision(&a, &b));

    //a.recalculate(1.5, 1, 1, 1, 0);
    a.rotate(-45);
    b.recalculate(2.6, 1, 1, 1, 0);
    assertFalse("No collision between two just separated, non-rotated rects", checkCollision(&a, &b));
}



void testCollisionCircleRect()
{
    BoundingCircle a(0.5, 1, 0.5, 0);
    BoundingRect b(1.5, 1, 1, 1, 0);

    assertTrue("Horizontal collision between circle and rect just touching", checkCollision(&a, &b));

    a.recalculate(1.5, 2, 1, 0, 0);
    assertTrue("Vertical collision between circle and rect just touching", checkCollision(&a, &b));

    b.rotate(45);
    assertTrue("Collision with rotated rectangle that would collide anyway", checkCollision(&a, &b));
    b.rotate(-45);

    a.translate(0, 0.1);
    assertFalse("No collision between circle and rect just separated", checkCollision(&a, &b));

    b.rotate(45);
    assertTrue("Collision with rotated rectangle that wouldn't collide otherwise", checkCollision(&a, &b));
}


void testCollisionCircleCircle(){
    BoundingCircle a(0, 0, 0.5, 0);
    BoundingCircle b(1, 0, 0.5, 0);

    assertTrue("Collision between two circles just colliding", checkCollision(&a, &b));

    b.translate(0, 0.5);
    assertFalse("No collision between two circles that would only collide if they were rects", checkCollision(&a, &b));
}


void performTests()
{
    testCollisionRectRect();
    testCollisionCircleRect();
    testCollisionCircleCircle();
}
