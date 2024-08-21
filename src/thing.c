#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#define COMMONLIB_IMPLEMENTATION
#include <commonlib.h>

#define WIDTH 1280
#define HEIGHT 720
#define GRAVITY 900.8f

#define DEBUG_TEXT(str, x, font_size, color) DrawText(str, x, y, font_size, WHITE); y+=font_size

STRUCT(Body);

struct Body {
    Vector3 pos, target, vel, acc;
    float radius, speed;
    Color color;
};

void draw_body(Body* body, bool debug);
void update_body(Body* body);
void do_physics_to_body(Body* body);
void control_body(Body* body);

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

    b.target = b.pos;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RED);

        if (IsKeyPressed(KEY_TAB)) {
            DEBUG_DRAW = !DEBUG_DRAW;
        }

        // TMP
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            b.pos.z = -(b.pos.y - GetMouseY());
        }

        control_body(&b);
        update_body(&b);
        draw_body(&b, DEBUG_DRAW);

        // DEBUG
        int y = 0;
        Arena_reset(&str_arena);
        cstr pos_str = Arena_alloc_str(str_arena, "pos: %.2f, %.2f, %.2f", b.pos.x, b.pos.y, b.pos.z);
        DEBUG_TEXT(pos_str, 0, 20, WHITE);

        EndDrawing();
    }

    Arena_free(&str_arena);
    CloseWindow();
    return 0;
}

void draw_body(Body* body, bool debug) {
    // shadow
    Vector2 l = { body->pos.x - body->radius, body->pos.y };
    Vector2 r = { body->pos.x + body->radius, body->pos.y };
    DrawLineV(l, r, BLACK);
    Vector2 t = { body->pos.x, body->pos.y - body->radius*0.5f };
    Vector2 b = { body->pos.x, body->pos.y + body->radius*0.5f };
    DrawLineV(t, b, BLACK);
    Vector2 zv = { 0.f, body->pos.z };
    Vector2 pos2 = { body->pos.x, body->pos.y };
    DrawCircleV(Vector2Add(pos2, zv), body->radius, body->color);
    if (debug) {
        Vector2 target2 = { body->target.x, body->target.y };
        DrawCircleV(target2, 2.f, BLUE);
    }
}

void update_body(Body* body) {
    const float rate = 0.99f;
    const float delta = GetFrameTime();
    body->pos.x = Lerp(body->pos.x, body->target.x, rate*delta);
    body->pos.y = Lerp(body->pos.y, body->target.y, rate*delta);

    // TMP
    if (body->pos.z < 0) body->acc.z += GRAVITY * delta;
    if (body->pos.z > 0) body->vel.z *= -0.99f;

    do_physics_to_body(body);
}

void do_physics_to_body(Body* body) {
    const float delta = GetFrameTime();
    body->vel = Vector3Add(body->vel, body->acc);
    body->pos = Vector3Add(body->pos, Vector3Scale(body->vel, delta));
    body->acc = Vector3Scale(body->acc, 0.f);
}

void control_body(Body* body) {
    Vector3 dir = {0};
    const float delta = GetFrameTime();
    if (IsKeyDown(KEY_LEFT)) {
        dir.x--;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        dir.x++;
    }
    if (IsKeyDown(KEY_UP)) {
        dir.y--;
    }
    if (IsKeyDown(KEY_DOWN)) {
        dir.y++;
    }

    // TMP
    if (IsKeyDown(KEY_Z)) {
        body->pos.z += 100.f * delta;
    }
    if (IsKeyDown(KEY_X)) {
        body->pos.z -= 100.f * delta;
    }

    dir = Vector3Normalize(dir);

    body->target = Vector3Add(body->target, Vector3Scale(dir, delta * body->speed));
}
