#include <iostream>
#include "lab1/var2/avl_tree.hpp"

using namespace std;

// Структура узла АВЛ дерева


// Функция для вычисления высоты узла
int height(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// Функция для вычисления балансировочного фактора
int balanceFactor(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// Функция для обновления высоты узла
void updateHeight(AVLNode* node) {
    node->height = 1 + max(height(node->left), height(node->right));
}

// Функция для левого поворота
AVLNode* leftRotate(AVLNode* y) {
    AVLNode* x = y->right;
    AVLNode* T2 = x->left;

    // Выполняем поворот
    x->left = y;
    y->right = T2;

    // Обновляем высоты
    updateHeight(y);
    updateHeight(x);

    // Возвращаем новый корень
    return x;
}

// Функция для правого поворота
AVLNode* rightRotate(AVLNode* x) {
    AVLNode* y = x->left;
    AVLNode* T2 = y->right;

    // Выполняем поворот
    y->right = x;
    x->left = T2;

    // Обновляем высоты
    updateHeight(x);
    updateHeight(y);

    // Возвращаем новый корень
    return y;
}

// Функция для вставки узла в АВЛ дерево
AVLNode* insert(AVLNode* node, int key) {
    // Базовый случай: дерево пустое
    if (node == nullptr) {
        return new AVLNode(key);
    }

    // Рекурсивная вставка в левое или правое поддерево
    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        // Ключ уже существует, проверяем флаг deleted
        if (node->deleted) {
            node->deleted = false; // Отменяем удаление
        }
        return node;
    }

    // Обновляем высоту текущего узла
    updateHeight(node);

    // Проверяем балансировочный фактор
    int balance = balanceFactor(node);

    // Левый-левый случай
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    // Правый-правый случай
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    // Левый-правый случай
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Правый-левый случай
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Дерево сбалансировано
    return node;
}

// Функция для ленивого удаления узла из АВЛ дерева
AVLNode* lazyDelete(AVLNode* node, int key) {
    // Находим узел для удаления
    AVLNode* nodeToDelete = findNode(node, key);

    // Если узел не найден, ничего не делаем
    if (nodeToDelete == nullptr) {
        return node;
    }

    // Устанавливаем флаг deleted = 1
    nodeToDelete->deleted = true;

    return node;
}

// Функция для поиска узла с заданным ключом
AVLNode* findNode(AVLNode* node, int key) {
    if (node == nullptr || node->key == key) {
        return node;
    }

    if (key < node->key) {
        return findNode(node->left, key);
    } else {
        return findNode(node->right, key);
    }
}

// Функция для подсчета количества удаленных узлов
int countDeletedNodes(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return (node->deleted ? 1 : 0) + countDeletedNodes(node->left) + countDeletedNodes(node->right);
}

// Функция для создания нового АВЛ дерева с неудалёнными узлами
AVLNode* rebuildTree(AVLNode* root) {
    // Подсчет количества удаленных узлов
    int deletedCount = countDeletedNodes(root);

    // Если нет удаленных узлов, ничего не делаем
    if (deletedCount == 0) {
        return root;
    }

    // Создание нового АВЛ дерева
    AVLNode* newRoot = nullptr;

    // Обход дерева и вставка неудалённых узлов в новое дерево
    inOrderTraversal(root, newRoot);
    

    return newRoot;
}

// Функция для обхода дерева в порядке возрастания ключей
void inOrderTraversal(AVLNode* node, AVLNode* newRoot) {
    if (node == nullptr) {
        return;
    }

    inOrderTraversal(node->left, newRoot);
    if (!node->deleted) {
        newRoot = insert(newRoot, node->key);
    }
    inOrderTraversal(node->right, newRoot);
}

// Функция для печати АВЛ дерева (для проверки)
void printTree(AVLNode* root, int level = 0) {
    if (root == nullptr) {
        return;
    }

    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++) {
        cout << " ";
    }
    cout << root->key << " (" << balanceFactor(root) << ")";
    if (root->deleted) {
        cout << " [deleted]" << endl;
    } else {
        cout << endl;
    }
    printTree(root->left, level + 1);
}

int main() {
    AVLNode* root = nullptr;
    int threshold = 3; // Пороговое значение для перестройки дерева

    // Вставка узлов
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);

    cout << "АВЛ дерево:" << endl;
    printTree(root);

    // Ленивое удаление
    root = lazyDelete(root, 30);

    cout << "\nАВЛ дерево после ленивого удаления:" << endl;
    printTree(root);

    // Вставка узла с удаленным ключом
    root = insert(root, 30);

    cout << "\nАВЛ дерево после вставки удаленного ключа:" << endl;
    printTree(root);

    // Ленивое удаление
    root = lazyDelete(root, 40);
    root = lazyDelete(root, 50);

    cout << "\nАВЛ дерево после удаления двух узлов:" << endl;
    printTree(root);

    // Проверка количества удаленных узлов
    int deletedCount = countDeletedNodes(root);
    cout << "\nКоличество удаленных узлов: " << deletedCount << endl;

    // Перестройка дерева
    if (deletedCount >= threshold) {
        root = rebuildTree(root);
        cout << "\nАВЛ дерево после перестройки:" << endl;
        printTree(root);
    }

    return 0;
}