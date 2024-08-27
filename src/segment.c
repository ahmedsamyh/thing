#include <segment.h>
#include <raymath.h>
#include <common.h>

void fix_seg_b_to_a(Segment* seg) {
    Vector2 dir = Vector2Normalize(Vector2Subtract(seg->b, seg->a));
    seg->b = Vector2Add(seg->a, Vector2Scale(dir, seg->length));
}

void fix_seg_a_to_b(Segment* seg) {
    Vector2 dir = Vector2Normalize(Vector2Subtract(seg->a, seg->b));
    seg->a = Vector2Add(seg->b, Vector2Scale(dir, seg->length));
}

void draw_segment(Segment* seg, bool debug) {
    (void)debug;
    DrawLineV(seg->a, seg->b, GetColor(0xB8BB26FF));
}
