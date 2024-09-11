#include <tree.h>
#include <momomath.h>

static void add_segs(Vector2 base, Segment** segments, int seg_count_min, int seg_count_max, float seg_len_min, float seg_len_max, float base_angle) {
    int seg_count = randomi(seg_count_min, seg_count_max);
    for (int i = 0; i < seg_count; ++i) {
        Segment seg;

        float d = 10.f;
        float angle = base_angle + randomf(-d, d);
        base_angle = angle;
        if (i == 0) {
            seg.a = base;
        } else {
            seg.a = (*segments)[i-1].b;
        }
        float length = randomf(seg_len_min, seg_len_max);
        seg.length = length;
        seg.b = Vector2Add(Vector2Scale(vector2_from_degrees(angle), length), seg.a);

        arrput(*segments, seg);
    }
}


static Leg branch_leg(Vector2 base, float base_angle) {
    Leg leg = {0};
    leg.start = base;

    add_segs(leg.start, &leg.segments, 5, 50, 1.f, 10.f, base_angle);
    leg.segment_count = arrlenu(leg.segments);
    leg.end = leg.segments[arrlenu(leg.segments)-1].b;

    return leg;
}

void init_tree(Tree* tree, Vector2 tree_base) {
    tree->base = tree_base;
    float base_angle = -90.f;
    int leg_count = randomi(3, 10);
    for (int i = 0; i < leg_count; ++i) {
        Leg leg = {0};
        if (i == 0) {
            leg = branch_leg(tree->base, base_angle);
        } else {
            leg = branch_leg(tree->legs[i-1].end, base_angle);
            for (int j = 0; j < randomi(0, 10); ++j) {
                Leg l = branch_leg(leg.end, base_angle);
                arrput(tree->legs, l);
            }
        }
        Segment last_seg = leg.segments[arrlenu(leg.segments)-1];
        base_angle = vector2_degrees(Vector2Subtract(last_seg.b, last_seg.a));

        arrput(tree->legs, leg);
    }


    // gravity
    /* float grav = 9.8f; */

}

void free_tree(Tree* tree) {
    arrfree(tree->legs);
}

void draw_tree(Tree* tree, bool debug) {
    for (int i = 0; i < arrlen(tree->legs); ++i) {
        draw_leg(&(tree->legs[i]), debug);
    }
    DrawCircleV(tree->base, 2.f, GREEN);
    (void)debug;
}

