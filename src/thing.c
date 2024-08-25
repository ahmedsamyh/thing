#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <body.h>
#include <config.h>
#include <segment.h>
#include <arm.h>
#include <bug.h>

#define COMMONLIB_IMPLEMENTATION
#include <commonlib.h>

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Thing");

    bool DEBUG_DRAW = false;
    Arena str_arena = Arena_make(0);

    Bug b = make_bug(CLITERAL(Vector2) {WIDTH*0.5f, HEIGHT*0.75f});

    /* Arm a = {0}; */
    /* init_arm(&a, 10, 50.f); */
    /* Vector2 target = {100.f, 100.f}; */

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(0x181818FF));
        /* Vector2 mpos = GetMousePosition(); */

        if (IsKeyPressed(KEY_TAB)) {
            DEBUG_DRAW = !DEBUG_DRAW;
        }

        //UPDATE////////////////////////////////////////////////////////////////////////////////////////////

        /* a.start = mpos; */
        /* update_arm_s2e(&a); */
        /* a.end = target; */
        /* update_arm_e2s(&a); */

        update_bug(&b);

        //DRAW//////////////////////////////////////////////////////////////////////////////////////////////
        /* draw_arm(&a, DEBUG_DRAW); */
        /* DrawCircleV(target, 12.f, RED); */

        draw_bug(&b, DEBUG_DRAW);

        // DEBUG
        int y = 0;
        Arena_reset(&str_arena);
        cstr fps_str = Arena_alloc_str(str_arena, "FPS: %d", GetFPS());
        DEBUG_TEXT(fps_str, 0, 20, WHITE);
        cstr pos_str = Arena_alloc_str(str_arena, "pos: %.2f, %.2f", b.body.pos.x, b.body.pos.y);
        DEBUG_TEXT(pos_str, 0, 20, WHITE);
        cstr last_dir_str = Arena_alloc_str(str_arena, "last_dir: %.2f, %.2f", b.body.last_dir.x, b.body.last_dir.y);
        DEBUG_TEXT(last_dir_str, 0, 20, WHITE);

        cstr dist_to_end_anchor_str = Arena_alloc_str(str_arena, "dist_to_end_anchor: %f / %f", b.dist_to_end_anchor[0], BUG_ARM_END_ANCHOR_MAX_DIST);
        DEBUG_TEXT(dist_to_end_anchor_str, 0, 20, WHITE);
        cstr bug_arm_state_str = Arena_alloc_str(str_arena, "bug_arm_state: %s", bug_arm_state_as_str(b.arm_states[0]));
        DEBUG_TEXT(bug_arm_state_str, 0, 20, WHITE);

        EndDrawing();
    }

    Arena_free(&str_arena);
    CloseWindow();
    return 0;
}
