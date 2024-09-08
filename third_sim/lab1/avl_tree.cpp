#include <iostream>

typedef struct avltree{
	int key;
	char *value;
	bool isDeleted;

	int height;
	avltree *left;
	avltree *right;
}avltree;

class AVLTree {
public:
	AVLTree() : root(nullptr) {}

	void avltree_add(int key, char *value){
		root = avltree_add(root, key, value);
	}

	void avltree_print_dfs(int level) {
        avltree_print_dfs(root, level);
    }

	void avltree_lazy_delete(int key) {
		root = avltree_lazy_delete(root, key);
	}


private:
    avltree* root;

	void avltree_print_dfs(struct avltree *root, int level) {
		if (root == nullptr)
            return;

        avltree_print_dfs(root->left, level + 1);
        for (int i = 0; i < level; i++)
            std::cout << "    ";
        std::cout << root->key << " - " << root->value << "\n";
        avltree_print_dfs(root->right, level + 1);
	}

	int imax2(int i, int j) {
		return (i > j)? i : j;
	}

	avltree* avltree_add(avltree* root, int key, char *value) {

		if (root == nullptr) {
			return avltree_create(key, value);
		}
		
		if (key < root -> key) {
			root -> left = avltree_add(root->left, key, value);
			if (avltree_height(root->left) - avltree_height(root->right) == 2) {
				if (key < root->left->key) {
                    root = avltree_right_rotate(root);
                } else {
                    root = avltree_leftright(root);
                }
			}
		}

		else if (key > root -> key) {
			root->right = avltree_add(root->right, key, value);
			if (avltree_height(root->right) - avltree_height(root->left) == 2) {
				if (key > root->right->key) {
                    root = avltree_left_rotate(root);
                } else {
                    root = avltree_rightleft(root);
                }
			}
		}

		root->height = imax2(avltree_height(root->left), avltree_height(root->right)) + 1;

		return root;
	}

	avltree* avltree_create(int key, char *value) { 
		avltree* node;

		node = new avltree;
		if (node != nullptr) {
			node -> key = key;
            node -> value = value;
            node -> isDeleted = false;
            node -> height = 0;
            node -> left = nullptr;
            node -> right = nullptr;
		}
		return node;
	}

	int avltree_height(avltree* node) {
		return (node != nullptr) ? node->height : -1;
	}

	int avltree_balance(avltree* node) {
		return avltree_height(node->left) - avltree_height(node->right);
	}

	avltree* avltree_right_rotate(avltree* node) {
		avltree* left;

		left = node->left;
		node->left = left->right;
		left->right = node;

		node->height = imax2(avltree_height(node->left), avltree_height(node->right)) + 1;
		left->height = imax2(avltree_height(left->left), node->height) + 1;

		return left;
	}

	avltree* avltree_left_rotate(avltree* node) {
		avltree* right;

		right = node->right;
		node->right = right->left;
		right->left = node;

		node->height = imax2(avltree_height(node->left), avltree_height(node->right)) + 1;
		right->height = imax2(avltree_height(right->right), node->height) + 1;
		return right;
	}

	avltree* avltree_leftright(avltree* node) {
        node->left = avltree_left_rotate(node->left);
        return avltree_right_rotate(node);
    }

	avltree* avltree_rightleft(avltree* node) {
		node->right = avltree_right_rotate(node->right);
        return avltree_left_rotate(node);
    }

	avltree* avltree_min(avltree* root) {
		while (root->left!= nullptr) {
            root = root->left;
        }
        return root;
	}

	avltree* avltree_max(avltree* root) {
		while (root->right!= nullptr) {
            root = root->right;
        }
        return root;
	}

	avltree* avltree_lazy_delete(avltree* root, int key) {
		if (root == nullptr) {
            return root;
        }

        if (key < root->key) {
            root->left = avltree_lazy_delete(root->left, key);
        } else if (key > root->key) {
            root->right = avltree_lazy_delete(root->right, key);
        } else {
            if (root->isDeleted) {
                return root;
            }
            root->isDeleted = true;
            return root;
        }

        if (root == nullptr) {
            return root;
        }

        root->height = imax2(avltree_height(root->left), avltree_height(root->right));
		int balance = avltree_balance(root);
		if (balance > 1) {
			if (avltree_balance(root->left) >= 0) {
                root = avltree_right_rotate(root);
            } else {
                root->left = avltree_left_rotate(root->left);
                root = avltree_right_rotate(root);
            }
        } else if (balance < -1) {
			if (avltree_balance(root->right) <= 0) {
				root = avltree_left_rotate(root);
            } else {
                root->right = avltree_right_rotate(root->right);
                root = avltree_left_rotate(root);
            }
        }
        return root;
	}
};