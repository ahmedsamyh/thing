#ifndef __ARM_H__
#define __ARM_H__

#include <segment.h>

STRUCT(Arm);

struct Arm {
    Segment* segments;
    float segment_length;
    size_t segment_count;
    Vector2 start, end;
};

void init_arm(Arm* arm, size_t seg_count, float seg_len);
void update_arm_s2e(Arm* arm);
void update_arm_e2s(Arm* arm);
void draw_arm(Arm* arm, bool debug);
void free_arm(Arm* arm);

#endif // __ARM_H__
