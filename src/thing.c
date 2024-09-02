#include <raylib.h>
#include <raymath.h>
#include <momomath.h>
#include <stdio.h>
#include <body.h>
#include <config.h>
#include <segment.h>
#include <leg.h>
#include <bug.h>

#define COMMONLIB_IMPLEMENTATION
#include <commonlib.h>

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Thing");

    bool DEBUG_DRAW = false;
    Arena str_arena = Arena_make(0);

    Bug b = make_bug(CLITERAL(Vector2) {WIDTH*0.5f, HEIGHT*0.75f});

    /* Leg a = {0}; */
    /* init_leg(&a, 10, 50.f); */
    /* Vector2 target = {WIDTH*0.5f, HEIGHT*0.5f}; */
    Camera2D camera = {
        .offset = { WIDTH*0.5f, HEIGHT*0.5f },
        .zoom = 1.f
    };
    Vector2 camera_target = b.body.pos;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(0x181818FF));
        /* Vector2 mpos = GetMousePosition(); */
        float delta = GetFrameTime();

        if (IsKeyPressed(KEY_TAB)) {
            DEBUG_DRAW = !DEBUG_DRAW;
        }

        //UPDATE////////////////////////////////////////////////////////////////////////////////////////////

        /* a.start = mpos; */
        /* update_leg_s2e(&a); */
        /* a.end = target; */
        /* update_leg_e2s(&a); */

        update_bug(&b);

        float R = 2.f * delta;
        camera_target.x = Lerp(camera_target.x, b.body.pos.x, R);
        camera_target.y = Lerp(camera_target.y, b.body.pos.y, R);
        camera.target = camera_target;

        //DRAW//////////////////////////////////////////////////////////////////////////////////////////////
        /* draw_leg(&a, DEBUG_DRAW); */
        /* DrawCircleV(target, 12.f, RED); */

        BeginMode2D(camera);
        draw_bug(&b, DEBUG_DRAW);
        EndMode2D();

        // DEBUG
        int y = 0;
        Arena_reset(&str_arena);
        cstr fps_str = Arena_alloc_str(str_arena, "FPS: %d", GetFPS());
        DEBUG_TEXT(fps_str, 0, 20, WHITE);
        cstr pos_str = Arena_alloc_str(str_arena, "pos: %.2f, %.2f", b.body.pos.x, b.body.pos.y);
        DEBUG_TEXT(pos_str, 0, 20, WHITE);
        cstr last_dir_str = Arena_alloc_str(str_arena, "last_dir: %.2f, %.2f", b.body.last_dir.x, b.body.last_dir.y);
        DEBUG_TEXT(last_dir_str, 0, 20, WHITE);

        cstr bug_leg_state_str = Arena_alloc_str(str_arena, "bug_leg_state: %s", bug_leg_state_as_str(b.leg_states[0]));
        DEBUG_TEXT(bug_leg_state_str, 0, 20, WHITE);

        EndDrawing();
    }

    Arena_free(&str_arena);
    CloseWindow();
    return 0;
}
