#include <leg.h>

void init_leg(Leg* a, size_t seg_count, float seg_len) {
    a->segment_count  = seg_count;
    arrsetlen(a->segments, seg_count);
    for (int i = 0; i < arrlen(a->segments); ++i) {
        a->segments[i].length = seg_len;
    }
}

void init_leg_diff_size(Leg* leg, size_t seg_count, float* seg_lens) {
    leg->segment_count  = seg_count;
    arrsetlen(leg->segments, seg_count);
    for (int i = 0; i < arrlen(leg->segments); ++i) {
        leg->segments[i].length = seg_lens[i];
    }
}

float get_leg_length(Leg* leg) {
    float length = 0.f;
    for (int i = 0; i < arrlen(leg->segments); ++i) {
        length += leg->segments[i].length;
    }
    return length;
}

//        a -> start
//       /
//      /       end
//     /         ^
//    /          |
//   b|a---------b
void update_leg_end_to_start(Leg* leg) {
    ASSERT(leg->segments);
    leg->segments[0].a = leg->start;
    fix_seg_b_to_a(&leg->segments[0]);
    for (int i = 1; i < arrlen(leg->segments); ++i) {
        Segment* seg = &leg->segments[i];
        Segment* prev = &leg->segments[i-1];
        seg->a = prev->b;
        fix_seg_b_to_a(seg);
    }
    leg->end = leg->segments[arrlenu(leg->segments)-1].b;
}

void update_leg_start_to_end(Leg* leg) {
    ASSERT(leg->segments);
    leg->segments[arrlenu(leg->segments)-1].b = leg->end;
    fix_seg_a_to_b(&leg->segments[arrlenu(leg->segments)-1]);
    for (int i = arrlenu(leg->segments)-1-1; i >= 0; --i) {
        Segment* seg = &leg->segments[i];
        Segment* next = &leg->segments[i+1];
        seg->b = next->a;
        fix_seg_a_to_b(seg);
    }
}

void draw_leg(Leg* leg, bool debug) {
    for (int i = 0; i < arrlen(leg->segments); ++i) {
        Segment* seg = &leg->segments[i];
        draw_segment(seg, debug);
    }
}

void free_leg(Leg* leg) {
    arrfree(leg->segments);
}
