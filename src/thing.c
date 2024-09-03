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

void draw_tile_grid(Camera2D camera);
void draw_chunk_grid(Camera2D camera);
void draw_origin_lines(Camera2D camera, Rectangle view_rect);

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Thing");

    bool DEBUG_DRAW = false;
    Arena str_arena = Arena_make(0);

    Bug b = make_bug(CLITERAL(Vector2) {WIDTH*0.5f, HEIGHT*0.75f});

    Camera2D camera = {
        .offset = { WIDTH*0.5f, HEIGHT*0.5f },
        .zoom = 1.f
    };
    Vector2 camera_target = b.body.pos;
    Rectangle view_rect = {
        .width = WIDTH,
        .height = HEIGHT,
    };
    /* Vector2 world_origin = { 0.f, 0.f }; */

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(0x181818FF));
        /* Vector2 mpos = GetMousePosition(); */
        float delta = GetFrameTime();

        if (IsKeyPressed(KEY_TAB)) {
            DEBUG_DRAW = !DEBUG_DRAW;
        }

        //UPDATE////////////////////////////////////////////////////////////////////////////////////////////

        update_bug(&b);

        float R = 2.f * delta;
        camera_target.x = Lerp(camera_target.x, b.body.pos.x, R);
        camera_target.y = Lerp(camera_target.y, b.body.pos.y, R);
        camera.target = camera_target;
        view_rect.x = camera.target.x - camera.offset.x;
        view_rect.y = camera.target.y - camera.offset.y;

        //DRAW//////////////////////////////////////////////////////////////////////////////////////////////


        BeginMode2D(camera);
            /* draw_tile_grid(camera); */
            draw_chunk_grid(camera);
            draw_origin_lines(camera, view_rect);
            draw_bug(&b, DEBUG_DRAW);
            /* DrawRectangleLinesEx(view_rect, 2.f, RED); */
        EndMode2D();


        // DEBUG
        int y = 0;
        Arena_reset(&str_arena);
        cstr fps_str = Arena_alloc_str(str_arena, "FPS: %d", GetFPS());
        DEBUG_TEXT(fps_str, 0, 20, WHITE);
        cstr pos_str = Arena_alloc_str(str_arena, "pos: %d, %d", (int)b.body.pos.x, (int)b.body.pos.y);
        DEBUG_TEXT(pos_str, 0, 20, WHITE);
        cstr view_rect_str = Arena_alloc_str(str_arena, "view_rect: %d, %d, %d, %d", (int)view_rect.x, (int)view_rect.y, (int)view_rect.width, (int)view_rect.height);
        DEBUG_TEXT(view_rect_str, 0, 20, WHITE);
        /* cstr last_dir_str = Arena_alloc_str(str_arena, "last_dir: %.2f, %.2f", b.body.last_dir.x, b.body.last_dir.y); */
        /* DEBUG_TEXT(last_dir_str, 0, 20, WHITE); */

        /* cstr bug_leg_state_str = Arena_alloc_str(str_arena, "bug_leg_state: %s", bug_leg_state_as_str(b.leg_states[0])); */
        /* DEBUG_TEXT(bug_leg_state_str, 0, 20, WHITE); */

        EndDrawing();
    }

    Arena_free(&str_arena);
    CloseWindow();
    return 0;
}

void draw_tile_grid(Camera2D camera) {
    Vector2 zerozero = { 0.f, 0.f };
    Vector2 world_topleft = GetScreenToWorld2D(zerozero, camera);
    Vector2 world_topleft_tile_aligned = {
        .x = ((int)world_topleft.x / (int)TILE_SIZE)*TILE_SIZE,
        .y = ((int)world_topleft.y / (int)TILE_SIZE)*TILE_SIZE,
    };

    for (float y = -1; y < ROWS+1; ++y) {
        for (float x = -1; x < COLS+1; ++x) {
            {
                Vector2 s = {
                    .x = 0.f,
                    .y = y * TILE_SIZE
                };
                s = Vector2Add(s, world_topleft_tile_aligned);
                Vector2 e = {
                    .x = WIDTH,
                    .y = y * TILE_SIZE
                };
                e = Vector2Add(e, world_topleft_tile_aligned);
                DrawLineV(s, e, ColorAlpha(WHITE, 0.1f));
            }
            {
                Vector2 s = {
                    .x = x * TILE_SIZE,
                    .y = 0.f,
                };
                s = Vector2Add(s, world_topleft_tile_aligned);
                Vector2 e = {
                    .x = x * TILE_SIZE,
                    .y = HEIGHT,
                };
                e = Vector2Add(e, world_topleft_tile_aligned);
                DrawLineV(s, e, ColorAlpha(WHITE, 0.1f));
            }
        }
    }
}

// TODO: Still is kinda sketchy
void draw_chunk_grid(Camera2D camera) {
    Vector2 zerozero = { 0.f, 0.f };
    Vector2 world_topleft = GetScreenToWorld2D(zerozero, camera);
    Vector2 world_topleft_chunk_aligned = {
        .x = ((int)world_topleft.x / (int)CHUNK_SIZE)*CHUNK_SIZE,
        .y = ((int)world_topleft.y / (int)CHUNK_SIZE)*CHUNK_SIZE,
    };

    float threshold = 10.f;
    for (float y = -threshold; y < ROWS+threshold; ++y) {
        for (float x = -threshold; x < COLS+threshold; ++x) {
            {
                Vector2 s = {
                    .x = 0.f,
                    .y = y * CHUNK_SIZE
                };
                s = Vector2Add(s, world_topleft_chunk_aligned);
                Vector2 e = {
                    .x = WIDTH,
                    .y = y * CHUNK_SIZE
                };
                e = Vector2Add(e, world_topleft_chunk_aligned);
                DrawLineV(s, e, ColorAlpha(WHITE, 0.1f));
            }
            {
                Vector2 s = {
                    .x = x * CHUNK_SIZE,
                    .y = 0.f,
                };
                s = Vector2Add(s, world_topleft_chunk_aligned);
                Vector2 e = {
                    .x = x * CHUNK_SIZE,
                    .y = HEIGHT,
                };
                e = Vector2Add(e, world_topleft_chunk_aligned);
                DrawLineV(s, e, ColorAlpha(WHITE, 0.1f));
            }
        }
    }
}

void draw_origin_lines(Camera2D camera, Rectangle view_rect) {
    if (-view_rect.height <= view_rect.y && view_rect.y <= 0.f) {
        Vector2 left_zero = { 0.f, 0.f };
        Vector2 right_zero = { view_rect.width, 0.f };
        left_zero = GetScreenToWorld2D(left_zero, camera);
        left_zero.y = 0.f;
        right_zero = GetScreenToWorld2D(right_zero, camera);
        right_zero.y = 0.f;
        DrawLineV(left_zero, right_zero, WHITE);
    }

    if (-view_rect.width <= view_rect.x && view_rect.x <= 0.f) {
        Vector2 top_zero = { 0.f, 0.f };
        Vector2 bot_zero = { 0.f, view_rect.height };
        top_zero = GetScreenToWorld2D(top_zero, camera);
        top_zero.x = 0.f;
        bot_zero = GetScreenToWorld2D(bot_zero, camera);
        bot_zero.x = 0.f;
        DrawLineV(top_zero, bot_zero, WHITE);
    }
}
