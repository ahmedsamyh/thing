#include <body.h>
#include <raymath.h>
#include <config.h>
#include <common.h>

void draw_body(Body* body, bool debug) {
    // shadow
    Vector2 l = { body->pos.x - body->radius, body->pos.y };
    Vector2 r = { body->pos.x + body->radius, body->pos.y };
    DrawLineV(l, r, BLACK);
    Vector2 t = { body->pos.x, body->pos.y - body->radius*0.5f };
    Vector2 b = { body->pos.x, body->pos.y + body->radius*0.5f };
    DrawLineV(t, b, BLACK);

    DrawCircleV(body->pos, body->radius, body->color);
    if (debug) {
        DrawCircleV(body->target, 2.f, BLUE);
        DrawLineV(body->pos, Vector2Add(body->pos, Vector2Scale(body->last_dir, 100.f)), WHITE);
    }
}

void update_body(Body* body) {
    const float rate = 2.f;
    const float delta = GetFrameTime();
    body->pos.x = Lerp(body->pos.x, body->target.x, rate*delta);
    body->pos.y = Lerp(body->pos.y, body->target.y, rate*delta);

    /* do_physics_to_body(body); */

    if (body->moving) {
        body->last_dir = Vector2Normalize(Vector2Subtract(body->target, body->pos));
    }
}

/* void do_physics_to_body(Body* body) { */
/*     const float delta = GetFrameTime(); */
/*     body->vel = Vector2Add(body->vel, body->acc); */
/*     body->pos = Vector2Add(body->pos, Vector2Scale(body->vel, delta)); */
/*     body->acc = Vector2Scale(body->acc, 0.f); */
/* } */

void control_body(Body* body) {
    Vector2 dir = {0};
    const float delta = GetFrameTime();
    body->moving = false;

    if (IsKeyDown(KEY_LEFT)) {
        dir.x--;
        body->moving = true;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        dir.x++;
        body->moving = true;
    }
    if (IsKeyDown(KEY_UP)) {
        dir.y--;
        body->moving = true;
    }
    if (IsKeyDown(KEY_DOWN)) {
        dir.y++;
        body->moving = true;
    }

    dir = Vector2Normalize(dir);

    body->target = Vector2Add(body->target, Vector2Scale(dir, delta * body->speed));
}
