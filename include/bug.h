#ifndef __BUG_H__
#define __BUG_H__

#include <arm.h>
#include <body.h>

STRUCT(Bug);
ENUM(Bug_arm_state);

#define BUG_ARM_SEG_COUNT 10
#define BUG_ARM_COUNT 2
#define BUG_RADIUS 32.f
#define BUG_ARM_LENGTH 32.f
#define BUG_ARM_END_ANCHOR_LENGTH (BUG_ARM_LENGTH * 1.85f)
#define BUG_ARM_END_ANCHOR_MAX_DIST (BUG_ARM_LENGTH * (BUG_ARM_SEG_COUNT-1)) // max distance the arm end can be from the arm anchor

enum Bug_arm_state {
    BUG_ARM_STATE_IDLE,   // arm end does not do anything
    BUG_ARM_STATE_FOLLOW, // arm end reaches the arm anchor
    BUG_ARM_STATE_COUNT
};

struct Bug {
    Body body;
    Arm arms[BUG_ARM_COUNT];
    Vector2 arm_end_anchors[BUG_ARM_COUNT];
    Bug_arm_state arm_states[BUG_ARM_COUNT];
    Vector2 arm_end_targets[BUG_ARM_COUNT];
    float dist_to_end_anchor[BUG_ARM_COUNT];
};

Bug make_bug(Vector2 pos);
void update_bug(Bug* bug);
void draw_bug(Bug* bug, bool debug);

// misc
cstr bug_arm_state_as_str(Bug_arm_state s);

#endif // __BUG_H__
