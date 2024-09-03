#include <tree.h>
#include <momomath.h>

Branch make_branch(Vector2 start) {
    Branch b;
    b.start = start;

    b.length = randomf(10.f, 100.f);
    float radians = randomf(0.f, TWO_PI);
    b.end = Vector2Add(b.start, Vector2Scale(vector2_from_radians(radians), b.length));

    b.branching_value = randomu8(0, 255);

    return b;
}

void init_tree(Tree* tree) {
    (void)tree;
}

void draw_tree(Tree* tree, bool debug);

