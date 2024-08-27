#include <bug.h>
#include <raymath.h>
#include <momomath.h>


void update_leg_anchors(Bug* bug) {
    {
        Vector2 last_dir_normal = { -bug->body.last_dir.y, bug->body.last_dir.x };
        bug->leg_end_anchors[0] = Vector2Add(bug->body.pos, Vector2Scale(last_dir_normal, BUG_LEG_END_ANCHOR_LENGTH));
    }
    {
        Vector2 last_dir_normal = { bug->body.last_dir.y, -bug->body.last_dir.x };
        bug->leg_end_anchors[1] = Vector2Add(bug->body.pos, Vector2Scale(last_dir_normal, BUG_LEG_END_ANCHOR_LENGTH));
    }
}

Bug make_bug(Vector2 pos) {
    Bug b = {0};
    b.body.pos = pos;
    b.body.target = pos;
    b.body.radius = BUG_RADIUS;
    b.body.speed = 400.f;
    b.body.color = GetColor(0xFB4934FF);
    b.body.last_dir.x = 1.f;

    // init legs
    for (int i = 0; i < BUG_LEG_COUNT; ++i) {
        init_leg(&b.legs[i], BUG_LEG_SEG_COUNT, BUG_LEG_LENGTH); // @TODO: Hardcoded leg segment length
        b.legs[i].start = pos;
    }
    update_leg_anchors(&b);
    for (int i = 0; i < BUG_LEG_COUNT; ++i) {
        b.leg_end_targets[i] = b.leg_end_anchors[i];
    }

    return b;
}

bool is_any_leg_moving(Bug* bug) {
    for (int i=0; i < BUG_LEG_COUNT; ++i) {
        if (bug->leg_states[i] == BUG_LEG_STATE_MOVE) {
            return true;
        }
    }
    return false;
}

// @TODO: Could optimize somehow (we are calculating dist_to_end_anchor twice)
int farthest_leg_from_anchor(Bug* bug) {
    int farthest_leg = 0;
    float farthest_leg_dist = 0.f;
    for (int i = 0; i < BUG_LEG_COUNT; ++i) {
        float dist_to_end_anchor = Vector2Length(Vector2Subtract(bug->leg_end_anchors[i], bug->leg_end_targets[i]));
        if (dist_to_end_anchor > farthest_leg_dist) {
            farthest_leg_dist = dist_to_end_anchor;
            farthest_leg = i;
        }
    }
    return farthest_leg;
}


int current_leg = 0;

void update_bug(Bug* bug) {
    const float delta = GetFrameTime();
    control_body(&bug->body);
    update_body(&bug->body);

    update_leg_anchors(bug);

    // @TODO: Teleport leg_end_target if it is too far from anchor
    if (!is_any_leg_moving(bug)) {
        current_leg = farthest_leg_from_anchor(bug);
    }
    {
        float dist_to_end_anchor = Vector2Length(Vector2Subtract(bug->leg_end_anchors[current_leg], bug->leg_end_targets[current_leg]));
        switch (bug->leg_states[current_leg]) {
            case BUG_LEG_STATE_IDLE: {
                if (dist_to_end_anchor > BUG_LEG_END_ANCHOR_MAX_DIST) {
                    bug->leg_states[current_leg] = BUG_LEG_STATE_MOVE;
                }
            } break;
            case BUG_LEG_STATE_MOVE: {
                /* float rate = 0.5f; */
                Vector2 to_anchor = Vector2Normalize(Vector2Subtract(bug->leg_end_anchors[current_leg], bug->leg_end_targets[current_leg]));
                /* bug->leg_end_targets[i].x = Lerp(bug->leg_end_targets[i].x, bug->leg_end_anchors[i].x, rate); */
                /* bug->leg_end_targets[i].y = Lerp(bug->leg_end_targets[i].y, bug->leg_end_anchors[i].y, rate); */

                bug->leg_end_targets[current_leg] = Vector2Add(bug->leg_end_targets[current_leg], Vector2Scale(to_anchor, 1000.f*delta));

                if (dist_to_end_anchor <= 0.75f) {
                    bug->leg_states[current_leg] = BUG_LEG_STATE_IDLE;
                    bug->leg_end_targets[current_leg] = bug->leg_end_anchors[current_leg];
                }
            } break;
            case BUG_LEG_STATE_COUNT:
            default: ASSERT(0 && "Unreachable!");
        }
    }

    // update legs
    // make the legs not bend downwards
    /* for (int i = 0; i < BUG_LEG_COUNT; ++i) { */
    /*     float leg_seg1_degrees = vector2_degrees(Vector2Subtract(bug->legs[i].segments[0].b, bug->legs[i].segments[0].a)); */
    /*     if (leg_seg1_degrees > 0.f) { */
    /*         Vector2 v = {0.f, -1.f}; */
    /*         bug->legs[i].segments[0].b = Vector2Add(bug->legs[i].segments[0].a, v); */
    /*     } */
    /* } */

    // attach leg end to it's target
    for (int i = 0; i < BUG_LEG_COUNT; ++i) {
        bug->legs[i].end = bug->leg_end_targets[i];
        update_leg_e2s(&bug->legs[i]);
    }

    // attach leg base(start) to body
    for (int i = 0; i < BUG_LEG_COUNT; ++i) {
        bug->legs[i].start = bug->body.pos;
        update_leg_s2e(&bug->legs[i]);
    }
}

void draw_bug(Bug* bug, bool debug) {
    draw_body(&bug->body, debug);
    for (int i = 0; i < BUG_LEG_COUNT; ++i) {
        draw_leg(&bug->legs[i], debug);
    }

    if (debug) {
        DrawLineV(bug->body.pos, bug->body.target, BLUE);
        for (int i = 0; i < BUG_LEG_COUNT; ++i) {
            DrawLineV(bug->body.pos, bug->leg_end_anchors[i], WHITE);
            DrawCircleV(bug->leg_end_targets[i], 6.f, (i == current_leg ? GetColor(0x8EC07CFF) : GetColor(0xD3869BFF)));
            DrawCircleV(bug->leg_end_anchors[i], 6.f, GetColor(0xD3869BFF));
        }
    }
}

cstr bug_leg_state_as_str(Bug_leg_state s) {
    switch (s) {
        case BUG_LEG_STATE_IDLE: { return "BUG_LEG_STATE_IDLE"; }
        case BUG_LEG_STATE_MOVE: { return "BUG_LEG_STATE_MOVE"; }
        case BUG_LEG_STATE_COUNT:
        default: ASSERT(0 && "Unreachable!");
    }
    return "INVALID LEG STATE STR!";
}
