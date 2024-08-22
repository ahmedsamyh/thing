#include <segment.h>
#include <raymath.h>
#include <common.h>

void fix_seg_b_to_a(Segment* seg) {
    Vector3 dir = Vector3Normalize(Vector3Subtract(seg->b, seg->a));
    seg->b = Vector3Add(seg->a, Vector3Scale(dir, seg->length));
}

void draw_segment(Segment* seg, bool debug) {
    (void)debug;
    Vector2 a2 = vec3_to_vec2(seg->a);
    Vector2 b2 = vec3_to_vec2(seg->b);
    DrawLineV(a2, b2, GREEN);
}
