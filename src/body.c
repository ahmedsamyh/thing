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

    Vector2 pos2 = vec3_to_vec2(body->pos);
    DrawCircleV(pos2, body->radius, body->color);
    if (debug) {
        Vector2 target2 = vec3_to_vec2(body->target);
        DrawCircleV(target2, 2.f, BLUE);
    }
}

void update_body(Body* body) {
    const float rate = 2.f;
    const float delta = GetFrameTime();
    body->pos.x = Lerp(body->pos.x, body->target.x, rate*delta);
    body->pos.y = Lerp(body->pos.y, body->target.y, rate*delta);

    // TMP
    if (body->pos.z < 0) body->acc.z += GRAVITY * delta;
    if (body->pos.z > 0) {
        body->pos.z = 0;
        body->vel.z *= -0.8f;
    }

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
