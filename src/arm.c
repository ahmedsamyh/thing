#include <arm.h>

Arm make_arm(size_t seg_count, float seg_len) {
    Arm a = {0};
    a.segment_length = seg_len;
    a.segment_count  = seg_count;
    arrsetlen(a.segments, seg_count);
    for (int i = 0; i < arrlen(a.segments); ++i) {
        a.segments[i].length = seg_len;
    }
    return a;
}

void update_arm(Arm* arm) {
    ASSERT(arm->segments);
    arm->segments[0].a = arm->pos;
    fix_seg_b_to_a(&arm->segments[0]);
    for (int i = 1; i < arrlen(arm->segments); ++i) {
        Segment* seg = &arm->segments[i];
        Segment* prev = &arm->segments[i-1];
        seg->a = prev->b;
        fix_seg_b_to_a(seg);
    }
}

void draw_arm(Arm* arm, bool debug) {
    for (int i = 0; i < arrlen(arm->segments); ++i) {
        Segment* seg = &arm->segments[i];
        draw_segment(seg, debug);
    }
}

void free_arm(Arm* arm) {
    arrfree(arm->segments);
}
