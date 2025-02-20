#pragma once
#include <string>

using std::string;

typedef struct Rbtree
{
    bool color;

    string *key;
    int value;

    Rbtree *left;
    Rbtree *right;
    Rbtree *parent;
}Rbtree;

Rbtree *rbCreate(string *key, int value);
Rbtree *rbAdd(Rbtree *root, Rbtree *node);
Rbtree *rbLookup(Rbtree *root, string *key);
Rbtree *rbRemove(Rbtree *root, string *key);
Rbtree *rbMin(Rbtree *root);
Rbtree *rbMax(Rbtree *root);

int rbInit();
int rbDeinit();

void free(Rbtree *root);
void rbPrintDfs(Rbtree *root, int level);
