#ifndef __ARM_H__
#define __ARM_H__

#include <segment.h>

STRUCT(Leg);

struct Leg {
    Segment* segments;
    float segment_length;
    size_t segment_count;
    Vector2 start, end;
};

void init_leg(Leg* leg, size_t seg_count, float seg_len);
void update_leg_end_to_start(Leg* leg);
void update_leg_start_to_end(Leg* leg);
void draw_leg(Leg* leg, bool debug);
void free_leg(Leg* leg);

#endif // __ARM_H__
