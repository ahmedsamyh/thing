#include <bug.h>
#include <raymath.h>

Bug make_bug(Vector2 pos) {
    Bug b = {0};
    b.body.pos = pos;
    b.body.target = pos;
    b.body.radius = BUG_RADIUS;
    b.body.speed = 200.f;
    b.body.color = YELLOW;
    b.body.last_dir.x = 1.f;

    // init arms
    for (int i = 0; i < BUG_ARM_COUNT; ++i) {
        init_arm(&b.arms[i], BUG_ARM_SEG_COUNT, BUG_ARM_LENGTH); // @TODO: Hardcoded arm segment length
        b.arms[i].start = pos;
    }

    return b;
}

void update_bug(Bug* bug) {
    /* const float delta = GetFrameTime(); */
    control_body(&bug->body);
    update_body(&bug->body);

    // update arms end_anchor
    {
        Vector2 last_dir_normal = { -bug->body.last_dir.y, bug->body.last_dir.x };
        bug->arm_end_anchors[0] = Vector2Add(bug->body.pos, Vector2Scale(last_dir_normal, BUG_ARM_END_ANCHOR_LENGTH));
    }
    {
        Vector2 last_dir_normal = { bug->body.last_dir.y, -bug->body.last_dir.x };
        bug->arm_end_anchors[1] = Vector2Add(bug->body.pos, Vector2Scale(last_dir_normal, BUG_ARM_END_ANCHOR_LENGTH));
    }

    for (int i = 0; i < 2; ++i) {
        bug->dist_to_end_anchor[i] = Vector2Length(Vector2Subtract(bug->arm_end_anchors[i], bug->arm_end_targets[i]));
        switch (bug->arm_states[i]) {
            case BUG_ARM_STATE_IDLE: {
                                         if (bug->dist_to_end_anchor[i] > BUG_ARM_END_ANCHOR_MAX_DIST) {
                                             bug->arm_states[i] = BUG_ARM_STATE_FOLLOW;
                                         }
                                     } break;
            case BUG_ARM_STATE_FOLLOW: {
                                           float rate = 0.5f;
                                           bug->arm_end_targets[i].x = Lerp(bug->arm_end_targets[i].x, bug->arm_end_anchors[i].x, rate);
                                           bug->arm_end_targets[i].y = Lerp(bug->arm_end_targets[i].y, bug->arm_end_anchors[i].y, rate);

                                           if (bug->dist_to_end_anchor[i] <= 0.75f) {
                                             bug->arm_states[i] = BUG_ARM_STATE_IDLE;
                                             bug->arm_end_targets[i] = bug->arm_end_anchors[i];
                                           }
                                       } break;
            case BUG_ARM_STATE_COUNT:
            default: ASSERT(0 && "Unreachable!");
        }
    }

    // update arms
    for (int i = 0; i < BUG_ARM_COUNT; ++i) {
        bug->arms[i].end = bug->arm_end_targets[i];
        update_arm_e2s(&bug->arms[i]);
    }
    for (int i = 0; i < BUG_ARM_COUNT; ++i) {
        bug->arms[i].start = bug->body.pos;
        update_arm_s2e(&bug->arms[i]);
    }
}

void draw_bug(Bug* bug, bool debug) {
    draw_body(&bug->body, debug);
    for (int i = 0; i < BUG_ARM_COUNT; ++i) {
        draw_arm(&bug->arms[i], debug);
    }

    if (debug) {
        DrawLineV(bug->body.pos, bug->body.target, BLUE);
        for (int i = 0; i < BUG_ARM_COUNT; ++i) {
            DrawLineV(bug->body.pos, bug->arm_end_anchors[i], WHITE);
            DrawCircleV(bug->arm_end_anchors[i], 6.f, GetColor(0xD3869BFF));
            DrawCircleV(bug->arm_end_targets[i], 6.f, GetColor(0xB8BB26FF));
        }
    }
}

cstr bug_arm_state_as_str(Bug_arm_state s) {
    switch (s) {
        case BUG_ARM_STATE_IDLE: { return "BUG_ARM_STATE_IDLE"; }
        case BUG_ARM_STATE_FOLLOW: { return "BUG_ARM_STATE_FOLLOW"; }
        case BUG_ARM_STATE_COUNT:
        default: ASSERT(0 && "Unreachable!");
    }
    return "INVALID ARM STATE STR!";
}
