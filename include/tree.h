#ifndef __TREE_H__
#define __TREE_H__

#include <raylib.h>
#include <commonlib.h>

#define BRANCH_THRESHOLD 34

STRUCT(Tree);
STRUCT(Branch);

struct Branch {
    Vector2 start, end;
    float length;
    uint8 branching_value; // will branch if goes above a certain threshold
};

Branch make_branch(Vector2 start);

struct Tree {
    Branch* branches; // @dynamic-array
    Vector2 pos; // base of the tree
};

void init_tree(Tree* tree);
void draw_tree(Tree* tree, bool debug);

#endif // __TREE_H__
