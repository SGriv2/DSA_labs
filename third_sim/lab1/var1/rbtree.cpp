#include <iostream>

#include "rbtree.hpp"

enum
{
    BLACK = 0,
    RED = 1,
};

Rbtree *treeNull = nullptr;

int rbInit()
{
    treeNull = rbCreate(nullptr, -1);
    if (treeNull == nullptr)
        return 1;
    return 0;
}

int rbDeinit()
{
    delete[] treeNull;
    return 0;
}

Rbtree *rbCreate(string *key, int value)
{
    Rbtree *node = new Rbtree;
    if (node != nullptr)
    {
        node->key = key;
        node->value = value;
        node->color = BLACK;
        node->parent = treeNull;
        node->left = treeNull;
        node->right = treeNull;
    }
    return node;
};

static void rbRotateLeft(Rbtree **root, Rbtree *node)
{
    Rbtree *n = node->right;
    node->right = n->left;

    if (n->left != treeNull)
        n->left->parent = node;
    n->parent = node->parent;

    if (node->parent == treeNull)
        *root = n;
    else if (node == node->parent->left)
        node->parent->left = n;
    else
        node->parent->right = n;
    n->left = node;

    node->parent = n;
};

static void rbRotateRight(Rbtree **root, Rbtree *node)
{
    Rbtree *n = node->left;
    node->left = n->right;

    if (n->right != treeNull)
        n->right->parent = node;
    n->parent = node->parent;

    if (node->parent == treeNull)
        *root = n;
    else if (node == node->parent->right)
        node->parent->right = n;
    else
        node->parent->left = n;
    n->right = node;

    node->parent = n;
};

static Rbtree *rbAddFixup(Rbtree **root, Rbtree *node)
{
    while (node->parent->color == RED)
    {
        Rbtree *uncle = nullptr;

        if (node->parent == node->parent->parent->left)
        {
            uncle = node->parent->parent->right;
            if (uncle->color == RED)
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->right)
                {
                    node = node->parent;
                    rbRotateLeft(root, node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rbRotateRight(root, node->parent->parent);
            }
        }
        else
        {
            uncle = node->parent->parent->left;
            if (uncle->color == RED)
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    rbRotateRight(root, node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rbRotateLeft(root, node->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
    return *root;
};

static Rbtree *rbRemoveFixup(Rbtree **root, Rbtree *node)
{
    while (node != *root && node->color == BLACK)
    {
        Rbtree *brother = nullptr;

        if (node == node->parent->left)
        {
            brother = node->parent->right;
            if (brother->color == RED)
            {
                brother->color = BLACK;
                node->parent->color = RED;
                rbRotateLeft(root, node->parent);
                brother = node->parent->right;
            }
            if (brother->left->color == BLACK && brother->right->color == BLACK)
            {
                brother->color = RED;
                node = node->parent;
            }
            else
            {
                if (brother->right->color == BLACK)
                {
                    brother->left->color = BLACK;
                    brother->color = RED;
                    rbRotateRight(root, brother);
                    brother = node->parent->right;
                }
                brother->color = node->parent->color;
                node->parent->color = BLACK;
                brother->right->color = BLACK;
                rbRotateLeft(root, node->parent);
                node = *root;
            }
        }
        else
        {
            brother = node->parent->left;
            if (brother->color == RED)
            {
                brother->color = BLACK;
                node->parent->color = RED;
                rbRotateRight(root, node->parent);
                brother = node->parent->left;
            }
            if (brother->left->color == BLACK && brother->right->color == BLACK)
            {
                brother->color = RED;
                node = node->parent;
            }
            else
            {
                if (brother->left->color == BLACK)
                {
                    brother->right->color = BLACK;
                    brother->color = RED;
                    rbRotateLeft(root, brother);
                    brother = node->parent->left;
                }
                brother->color = node->parent->color;
                node->parent->color = BLACK;
                brother->left->color = BLACK;
                rbRotateRight(root, node->parent);
                node = *root;
            }
        }
    }
    node->color = BLACK;
    return *root;
};

void free(Rbtree *root)
{
    if (root == nullptr || root == treeNull)
        return;

    if (root->left != treeNull)
        free(root->left);
    if (root->right != treeNull)
        free(root->right);
    delete[] root;
};

static void rbPrintDfs(Rbtree *node, int level, int currentLevel)
{
    if (node == treeNull)
        return;

    if (currentLevel < level)
    {
        std::cout << "Level " << currentLevel << ": "
                  << "value: " << node->value
                  << ", Color: " << (node->color == RED ? "RED" : "BLACK") << "  " << (node == node->parent->left ? "LEFT" : "RIGHT") << std::endl;

        rbPrintDfs(node->left, level, currentLevel + 1);
        rbPrintDfs(node->right, level, currentLevel + 1);
    }
};

void rbPrintDfs(Rbtree *root, int level)
{
    int currentLevel = 0;
    std::cout << "Level " << currentLevel << ": "
              << "value: " << root->value
              << ", Color: " << (root->color == RED ? "RED" : "BLACK") << std::endl;
    rbPrintDfs(root->left, level, currentLevel + 1);
    rbPrintDfs(root->right, level, currentLevel + 1);
};

static void rbReplaceNode(Rbtree **root, Rbtree **n1, Rbtree **n2)
{
    if ((*n1)->parent == treeNull)
        *root = *n2;
    else if (*n1 == (*n1)->parent->left)
        (*n1)->parent->left = *n2;
    else
        (*n1)->parent->right = *n2;
    (*n2)->parent = (*n1)->parent;
};

Rbtree *rbAdd(Rbtree *root, Rbtree *node)
{
    Rbtree *parent = treeNull, *tempRoot = root;

    while (tempRoot != treeNull && tempRoot != nullptr)
    {
        parent = tempRoot;

        if (*(node->key) < *(tempRoot->key))
            tempRoot = tempRoot->left;
        else if (*(node->key) > *(tempRoot->key))
            tempRoot = tempRoot->right;
        else
            return root;
    }
    node->parent = parent;
    if (parent == treeNull || parent == nullptr)
        root = node;
    else
    {
        if (*(node->key) < *(parent->key))
            parent->left = node;
        else
            parent->right = node;

        node->left = treeNull;
        node->right = treeNull;
        node->color = RED;
        rbAddFixup(&root, node);
    }
    return root;
};

Rbtree *rbRemove(Rbtree *root, string *key)
{
    Rbtree *node = rbLookup(root, key);
    if (node == treeNull)
        return root;

    Rbtree *tNode = node, *child = nullptr;
    bool tNodeColor = tNode->color;

    if (node->left == treeNull)
    {
        child = node->right;
        rbReplaceNode(&root, &node, &node->right);
    }
    else if (node->right == treeNull)
    {
        child = node->left;
        rbReplaceNode(&root, &node, &node->left);
    }
    else
    {
        tNode = rbMin(node->right);
        tNodeColor = tNode->color;
        child = tNode->right;
        if (tNode->parent == node)
            child->parent = tNode;
        else
        {
            rbReplaceNode(&root, &tNode, &tNode->right);
            tNode->right = node->right;
            tNode->right->parent = tNode;
        }
        rbReplaceNode(&root, &node, &tNode);
        tNode->left = node->left;
        tNode->left->parent = tNode;
        tNode->color = node->color;
    }
    delete node;
    if (tNodeColor == BLACK)
        rbRemoveFixup(&root, child);
    return root;
};

Rbtree *rbLookup(Rbtree *root, string *key)
{
    if (root == nullptr)
        return root;

    Rbtree *tempRoot = root;

    while (tempRoot != treeNull)
    {
        if (*key == *(tempRoot->key))
            return tempRoot;
        else if (*key < *(tempRoot->key))
            tempRoot = tempRoot->left;
        else
            tempRoot = tempRoot->right;
    }
    return tempRoot;
};

Rbtree *rbMin(Rbtree *root)
{
    Rbtree *node = root;

    if (node != nullptr && node != treeNull)
        while (node->left != treeNull)
            node = node->left;
    return node;
};

Rbtree *rbMax(Rbtree *root)
{
    Rbtree *node = root;

    if (node != nullptr && node != treeNull)
        while (node->right != treeNull)
            node = node->right;
    return node;
};
