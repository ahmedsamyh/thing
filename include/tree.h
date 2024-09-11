#ifndef __TREE_H__
#define __TREE_H__

#include <raylib.h>
#include <commonlib.h>
#include <leg.h>

STRUCT(Tree);

struct Tree {
    Leg* legs; // @dynamic-array
    Vector2 base;
};

void init_tree(Tree* tree, Vector2 pos);
void free_tree(Tree* tree);
void draw_tree(Tree* tree, bool debug);

#endif // __TREE_H__
