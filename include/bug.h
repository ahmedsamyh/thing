#ifndef __BUG_H__
#define __BUG_H__

#include <leg.h>
#include <body.h>

STRUCT(Bug);
ENUM(Bug_leg_state);

#define BUG_LEG_SEG_COUNT 3
#define BUG_LEG_SEG_LENGTH 32.f
#define BUG_LEG_COUNT 2
#define BUG_RADIUS 16.f
#define BUG_LEG_END_ANCHOR_LENGTH BUG_LEG_SEG_LENGTH
/* #define BUG_LEG_END_ANCHOR_MAX_DIST (BUG_LEG_LENGTH * (BUG_LEG_SEG_COUNT-1)) // max distance the leg end can be from the leg anchor */

enum Bug_leg_state {
    BUG_LEG_STATE_IDLE,   // leg end does not do anything
    BUG_LEG_STATE_MOVE, // leg end reaches the leg anchor
    BUG_LEG_STATE_COUNT
};


struct Bug {
    Body body;
    Leg legs[BUG_LEG_COUNT];
    Vector2 leg_end_anchors[BUG_LEG_COUNT];
    Bug_leg_state leg_states[BUG_LEG_COUNT];
    Vector2 leg_end_targets[BUG_LEG_COUNT];
    int bug_leg_end_anchor_max_dist;
};

Bug make_bug(Vector2 pos);
void update_bug(Bug* bug);
void draw_bug(Bug* bug, bool debug);

// misc
cstr bug_leg_state_as_str(Bug_leg_state s);

#endif // __BUG_H__
