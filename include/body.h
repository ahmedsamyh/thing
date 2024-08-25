#ifndef __BODY_H__
#define __BODY_H__

#include <commonlib.h>
#include <raylib.h>

STRUCT(Body);

struct Body {
    Vector2 pos, target, vel, acc;
    Vector2 last_dir;
    float radius, speed;
    Color color;
    bool moving;
};

void draw_body(Body* body, bool debug);
void update_body(Body* body);
void do_physics_to_body(Body* body);
void control_body(Body* body);

#endif // __BODY_H__
