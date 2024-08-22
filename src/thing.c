#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <body.h>
#include <config.h>
#include <segment.h>
#include <arm.h>

#define COMMONLIB_IMPLEMENTATION
#include <commonlib.h>

void add_arm(Arm** arms, Vector2 pos, float length) {
    Arm a = make_arm(200, length);
    a.pos = CLITERAL(Vector3) { pos.x, pos.y, 0.f };
    arrput(*arms, a);
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Thing");

    bool DEBUG_DRAW = false;
    Arena str_arena = Arena_make(0);

    Body b = {
        .pos = { WIDTH*0.5f, HEIGHT * 0.85f , 0.f},
        .radius = 32.f,
        .speed = 200.f,
        .color = YELLOW,
    };

    Arm* arms = NULL; // @dynamic-array

    b.target = b.pos;

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

        control_body(&b);
        update_body(&b);

        for (int i = 0; i < arrlen(arms); ++i) {
            Arm* arm = &arms[i];
            arm->pos.x = mpos.x; arm->pos.y = mpos.y;
            update_arm(arm);
        }

        //DRAW//////////////////////////////////////////////////////////////////////////////////////////////
        for (int i = 0; i < arrlen(arms); ++i) {
            Arm* arm = &arms[i];
            draw_arm(arm, DEBUG_DRAW);
        }

        draw_body(&b, DEBUG_DRAW);

        // DEBUG
        int y = 0;
        Arena_reset(&str_arena);
        cstr fps_str = Arena_alloc_str(str_arena, "FPS: %d", GetFPS());
        DEBUG_TEXT(fps_str, 0, 20, WHITE);
        cstr pos_str = Arena_alloc_str(str_arena, "pos: %.2f, %.2f, %.2f", b.pos.x, b.pos.y, b.pos.z);
        DEBUG_TEXT(pos_str, 0, 20, WHITE);
        cstr arms_count_str = Arena_alloc_str(str_arena, "arms_count: %zu", arrlenu(arms));
        DEBUG_TEXT(arms_count_str, 0, 20, WHITE);

        EndDrawing();
    }

    Arena_free(&str_arena);
    arrfree(arms);
    CloseWindow();
    return 0;
}
