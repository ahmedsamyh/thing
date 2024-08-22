#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include <commonlib.h>
#include <raylib.h>

STRUCT(Segment);

struct Segment {
    Vector3 a, b;
    float length;
};

void fix_seg_b_to_a(Segment* seg);
void draw_segment(Segment* seg, bool debug);

#endif // __SEGMENT_H__
