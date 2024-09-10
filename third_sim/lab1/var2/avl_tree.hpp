typedef struct avltree{
	int key;
	char *value;
	bool isDeleted;

	int height;
	avltree *left;
	avltree *right;
}avltree;

void add(int key, char *value);
void print(int level);
void lazy_delete(int key);
void clear();
void avltree_print_dfs(struct avltree *root, int level);
int imax2(int i, int j);
avltree* avltree_add(avltree* root, int key, char *value);
avltree* avltree_create(int key, char *value);
int avltree_height(avltree* node);
int avltree_balance(avltree* node);
avltree* avltree_right_rotate(avltree* node);
avltree* avltree_left_rotate(avltree* node);
avltree* avltree_leftright(avltree* node);
avltree* avltree_rightleft(avltree* node);
avltree* avltree_min(avltree* root);
avltree* avltree_max(avltree* root);
avltree* avltree_lazy_deletion(avltree* root, int key);
avltree* avltree_free(avltree* node);
avltree* avltree_cleanup(avltree* node);
