#ifndef __BUG_H__
#define __BUG_H__

#include <arm.h>
#include <body.h>

STRUCT(Bug);

#define BUG_ARM_COUNT 2
#define BUG_RADIUS 32.f
#define BUG_ARM_TARGET_LENGTH (BUG_RADIUS * 1.5f)

struct Bug {
    Body body;
    Arm arms[BUG_ARM_COUNT];
    Vector2 arm_targets[BUG_ARM_COUNT];
};

Bug make_bug(Vector2 pos);
void update_bug(Bug* bug);
void draw_bug(Bug* bug, bool debug);

#endif // __BUG_H__
