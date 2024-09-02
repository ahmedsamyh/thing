#ifndef __ARM_H__
#define __ARM_H__

#include <segment.h>

STRUCT(Leg);

struct Leg {
    Segment* segments;
    size_t segment_count;
    Vector2 start, end;
};

void init_leg(Leg* leg, size_t seg_count, float seg_len);
// NOTE: seg_lens array must be exactly seg_count length!
void init_leg_diff_size(Leg* leg, size_t seg_count, float* seg_lens);
float get_leg_length(Leg* leg);
void update_leg_end_to_start(Leg* leg);
void update_leg_start_to_end(Leg* leg);
void draw_leg(Leg* leg, bool debug);
void free_leg(Leg* leg);

#endif // __ARM_H__
