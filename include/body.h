#ifndef __BODY_H__
#define __BODY_H__

#include <commonlib.h>
#include <raylib.h>

STRUCT(Body);

struct Body {
    Vector3 pos, target, vel, acc;
    float radius, speed;
    Color color;
};

void draw_body(Body* body, bool debug);
void update_body(Body* body);
void do_physics_to_body(Body* body);
void control_body(Body* body);

#endif // __BODY_H__
