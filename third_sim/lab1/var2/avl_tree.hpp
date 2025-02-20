struct avltree{
	int key;
	std::string value;
	bool deleted;

	int height;
	avltree *left;
	avltree *right;
};


void avltree_print_dfs(avltree *root, int level);
int imax2(int i, int j);
avltree* avltree_add(avltree* root, int key, std::string value);
avltree* avltree_create(int key, std::string value);
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
