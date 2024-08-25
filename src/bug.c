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
        init_arm(&b.arms[i], 2, 100.f); // @TODO: Hardcoded arm segment length
        b.arms[i].start = pos;
    }

    return b;
}

void update_bug(Bug* bug) {
    control_body(&bug->body);
    update_body(&bug->body);

    // update arms
    for (int i = 0; i < BUG_ARM_COUNT; ++i) {
        bug->arms[i].start = bug->body.pos;
        update_arm_s2e(&bug->arms[i]);
    }

    // update arms target
    {
        Vector2 last_dir_normal = { -bug->body.last_dir.y, bug->body.last_dir.x };
        bug->arm_targets[0] = Vector2Scale(last_dir_normal, BUG_ARM_TARGET_LENGTH);
    }
    {
        Vector2 last_dir_normal = { bug->body.last_dir.y, -bug->body.last_dir.x };
        bug->arm_targets[1] = Vector2Scale(last_dir_normal, BUG_ARM_TARGET_LENGTH);
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
            DrawLineV(bug->body.pos, Vector2Add(bug->body.pos, bug->arm_targets[i]), WHITE);
        }
    }
}
