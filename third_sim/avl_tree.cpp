#include <iostream>

struct Node {
    int key;
    bool isDeleted; // Флаг, указывающий на то, что узел помечен для удаления
    Node* left;
    Node* right;
    int height;

    Node(int key) : key(key), isDeleted(false), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void lazyDelete(int key) {
        root = lazyDelete(root, key);
    }

    void inOrder() {
        inOrder(root);
    }

    void cleanup() {
        root = cleanup(root);
    }


private:
    Node* root;

    

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(Node* node) {
        return height(node->left) - height(node->right);
    }

    void fixHeight(Node* node) {
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }

    Node* rotateRight(Node* node) {
        Node* left_child = node->left;
        node->left = left_child->right;
        left_child->right = node;
        fixHeight(node);
        fixHeight(left_child);
        return left_child;
    }

    Node* rotateLeft(Node* node) {
        Node* right_child = node->right;
        node->right = right_child->left;
        right_child->left = node;
        fixHeight(node);
        fixHeight(right_child);
        return right_child;
    }

    Node* balance(Node* node) {
        fixHeight(node);
        if (balanceFactor(node) == 2) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        if (balanceFactor(node) == -2) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }
        return balance(node);
    }

    Node* lazyDelete(Node* node, int key) {
        if (!node) return nullptr;
        if (key < node->key) {
            node->left = lazyDelete(node->left, key);
        } else if (key > node->key) {
            node->right = lazyDelete(node->right, key);
        } else {
            // Узел найден, помечаем его как удаленный
            node->isDeleted = true;
        }
        return balance(node);
    }
    
    void avltree_print_dfs(Node *root, int level) {
		if (root == nullptr)
            return;

        avltree_print_dfs(root->left, level + 1);
        std::cout << "\n";
        for (int i = 0; i < level; i++)
            std::cout << "    ";
        std::cout << root->key << "\n";
        avltree_print_dfs(root->right, level + 1);
	}

    void inOrder(Node* node) {
        int level = 0;
        if (!node) return;
        inOrder(node->left);
        if (!node->isDeleted) {
            avltree_print_dfs(node, level);
            level++;
        }
        inOrder(node->right);
    }

    Node* cleanup(Node* node) {
        if (!node) return nullptr;
        node->left = cleanup(node->left);
        node->right = cleanup(node->right);
        
        // Проверим, если узел помечен как удаленный и не имеет детей
        if (node->isDeleted && !node->left && !node->right) {
            delete node;
            return nullptr;
        }
        return node;
    }
};

int main() {
    AVLTree tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(10);
    tree.insert(25);

    tree.lazyDelete(30);
    std::cout << "Tree after lazy delete 30 (DFS): " << "\n";
    tree.inOrder();

    std::cout << "Tree elements (in-order): ";
    tree.inOrder();

    tree.lazyDelete(20);
    std::cout << "Tree after lazy delete 20 (in-order): ";
    tree.inOrder();

    tree.cleanup(); // Удаление помеченных узлов
    std::cout << "Tree after cleanup (in > Chat AI Bot - Chat GPT | Midjourney | Claude | Gemini: -order): ";
    tree.inOrder();

    return 0;
}

