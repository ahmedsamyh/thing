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

void add_arm(Arm** arms, Vector2 pos, float length) {
    Arm a = {0};
    init_arm(&a, 200, length);
    a.start = pos;
    arrput(*arms, a);
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Thing");

    bool DEBUG_DRAW = false;
    Arena str_arena = Arena_make(0);

    Bug b = make_bug(CLITERAL(Vector2) {WIDTH*0.5f, HEIGHT*0.75f});

    Arm* arms = NULL; // @dynamic-array

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RED);
        Vector2 mpos = GetMousePosition();

        if (IsKeyPressed(KEY_TAB)) {
            DEBUG_DRAW = !DEBUG_DRAW;
        }

        // TMP
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            add_arm(&arms, mpos, 10.f);
        }

        //UPDATE////////////////////////////////////////////////////////////////////////////////////////////

        update_bug(&b);

        for (int i = 0; i < arrlen(arms); ++i) {
            Arm* arm = &arms[i];
            arm->start.x = mpos.x; arm->start.y = mpos.y;
            update_arm_s2e(arm);
        }

        //DRAW//////////////////////////////////////////////////////////////////////////////////////////////
        for (int i = 0; i < arrlen(arms); ++i) {
            Arm* arm = &arms[i];
            draw_arm(arm, DEBUG_DRAW);
        }

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
        cstr arms_count_str = Arena_alloc_str(str_arena, "arms_count: %zu", arrlenu(arms));
        DEBUG_TEXT(arms_count_str, 0, 20, WHITE);

        EndDrawing();
    }

    Arena_free(&str_arena);
    arrfree(arms);
    CloseWindow();
    return 0;
}
