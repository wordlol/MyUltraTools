#pragma once
#include "ATD.h"
#include <algorithm>
#include <stdexcept>
//9
//Древовидные структуры(деревья бинарные, сбалансированные,
//сильноветвящиеся).Определить их словесно или с использованием схем
//Основные операции над ними(поиск, вставка, удаление).Показать
//вычислительную сложность.

//BST
template <typename K, typename V>
struct BSTNode {
    K key;
    V value;
    BSTNode* left = nullptr;
    BSTNode* right = nullptr;
    BSTNode(const K& k, const V& v) : key(k), value(v) {}
};

template <typename K, typename V>
class BST {
    BSTNode<K, V>* root = nullptr;
    size_t size_ = 0;
    BSTNode<K, V>* insertRec(BSTNode<K, V>* node, const K& key, const V& value) {
        if (!node) {
            ++size_;
            return new BSTNode<K, V>(key, value);
        }
        if (key < node->key)
            node->left = insertRec(node->left, key, value);
        else if (key > node->key)
            node->right = insertRec(node->right, key, value);
        else
            node->value = value;
        return node;
    }
    V* findRec(BSTNode<K, V>* node, const K& key) const {
        if (!node) return nullptr;
        if (key == node->key) return &node->value;
        if (key < node->key) return findRec(node->left, key);
        return findRec(node->right, key);
    }
    BSTNode<K, V>* removeRec(BSTNode<K, V>* node, const K& key) {
        if (!node) return nullptr;
        if (key < node->key) {
            node->left = removeRec(node->left, key);
        }
        else if (key > node->key) {
            node->right = removeRec(node->right, key);
        }
        else {
            // узел найден
            if (!node->left && !node->right) {
                delete node;
                --size_;
                return nullptr;
            }
            else if (!node->left) {
                BSTNode<K, V>* rightChild = node->right;
                delete node;
                --size_;
                return rightChild;
            }
            else if (!node->right) {
                BSTNode<K, V>* leftChild = node->left;
                delete node;
                --size_;
                return leftChild;
            }
            else {
                // два потомка: находим минимальный в правом поддереве
                BSTNode<K, V>* minNode = node->right;
                while (minNode->left) minNode = minNode->left;
                // копируем ключ и значение
                node->key = minNode->key;
                node->value = minNode->value;
                // удаляем минимальный узел из правого поддерева
                node->right = removeRec(node->right, minNode->key);
            }
        }
        return node;
    }
    void inorderRec(BSTNode<K, V>* node, std::vector<K>& out) const {
        if (!node) return;
        inorderRec(node->left, out);
        out.push_back(node->key);
        inorderRec(node->right, out);
    }
public:
    void insert(const K& key, const V& value) {
        root = insertRec(root, key, value);
    }
    V* find(const K& key) {
        return findRec(root, key);
    }
    void remove(const K& key) {
        root = removeRec(root, key);
    }
    size_t size() const { return size_; }
    void inorder(std::vector<K>& out) const {
        inorderRec(root, out);
    }
};


//AVL
template <typename K, typename V>
struct AVLNode {
    K key;
    V value;
    AVLNode* left = nullptr;
    AVLNode* right = nullptr;
    int height = 1;
    AVLNode(const K& k, const V& v) : key(k), value(v) {}
};

template <typename K, typename V>
class AVLTree {
    AVLNode<K, V>* root = nullptr;
    size_t size_ = 0;

    int height(AVLNode<K, V>* node) const {
        return node ? node->height : 0;
    }
    int balanceFactor(AVLNode<K, V>* node) const {
        return height(node->left) - height(node->right);
    }
    void updateHeight(AVLNode<K, V>* node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }
    AVLNode<K, V>* rotateRight(AVLNode<K, V>* y) {
        AVLNode<K, V>* x = y->left;
        AVLNode<K, V>* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;

    }
    AVLNode<K, V>* rotateLeft(AVLNode<K, V>* x) {
        AVLNode<K, V>* y = x->right;
        AVLNode<K, V>* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }
    AVLNode<K, V>* balance(AVLNode<K, V>* node) {
        updateHeight(node);
        int bf = balanceFactor(node);
        // Левое поддерево перевешивает
        if (bf > 1) {
            if (balanceFactor(node->left) < 0) // LR случай
                node->left = rotateLeft(node->left);
            return rotateRight(node); // LL или LR
        }
        // Правое поддерево перевешивает
        if (bf < -1) {
            if (balanceFactor(node->right) > 0) // RL случай
                node->right = rotateRight(node->right);
            return rotateLeft(node); // RR или RL
        }
        return node;
    }
    AVLNode<K, V>* insertRec(AVLNode<K, V>* node, const K& key, const V& value) {
        if (!node) {
            ++size_;
            return new AVLNode<K, V>(key, value);
        }
        if (key < node->key)
            node->left = insertRec(node->left, key, value);
        else if (key > node->key)
            node->right = insertRec(node->right, key, value);
        else {
            node->value = value;
            return node;
        }
        return balance(node);
    }
    V* findRec(AVLNode<K, V>* node, const K& key) const {
        if (!node) return nullptr;
        if (key == node->key) return &node->value;
        if (key < node->key) return findRec(node->left, key);
        return findRec(node->right, key);
    }
    AVLNode<K, V>* removeRec(AVLNode<K, V>* node, const K& key) {
        if (!node) return nullptr;
        if (key < node->key)
            node->left = removeRec(node->left, key);
        else if (key > node->key)
            node->right = removeRec(node->right, key);
        else {
            if (!node->left || !node->right) {
                AVLNode<K, V>* temp = node->left ? node->left : node->right;
                if (!temp) { // лист
                    delete node;
                    --size_;
                    return nullptr;
                }
                else {
                    *node = *temp; // копируем содержимое (осторожно с указателями)
                    delete temp;
                    --size_;
                }
            }
            else {
                AVLNode<K, V>* minNode = node->right;
                while (minNode->left) minNode = minNode->left;
                node->key = minNode->key;
                node->value = minNode->value;
                node->right = removeRec(node->right, minNode->key);
            }
        }
        return balance(node);
    }

public:
    void insert(const K& key, const V& value) {
        root = insertRec(root, key, value);
    }
    V* find(const K& key) {
        return findRec(root, key);
    }
    void remove(const K& key) {
        root = removeRec(root, key);
    }
    size_t size() const { return size_; }
    int getHeight() const { return height(root); }
};


//BTree
template <typename K, typename V>
struct BTreeNode {
    bool isLeaf;
    std::vector<K> keys;
    std::vector<V> values;
    std::vector<BTreeNode*> children;
    BTreeNode(bool leaf) : isLeaf(leaf) {}
};

// BTree.h – окончательная рабочая версия
template <typename K, typename V>
class BTree {
    static constexpr int T = 2;          // минимальная степень (2-3 дерево)
    struct Node {
        bool isLeaf;
        std::vector<K> keys;
        std::vector<V> values;
        std::vector<Node*> children;
        Node(bool leaf) : isLeaf(leaf) {}
    };
    Node* root;
    size_t count = 0;

    // Разделение заполненного ребёнка (child имеет 2*T-1 ключей)
    void splitChild(Node* parent, size_t idx, Node* child) {
        Node* newNode = new Node(child->isLeaf);

        // Сохраняем срединный ключ и значение ДО изменения child
        K medianKey = child->keys[T - 1];
        V medianValue = child->values[T - 1];

        // Переносим правую половину ключей и значений в newNode
        newNode->keys.assign(child->keys.begin() + T, child->keys.end());
        newNode->values.assign(child->values.begin() + T, child->values.end());

        if (!child->isLeaf) {
            // Переносим правую половину детей
            newNode->children.assign(child->children.begin() + T, child->children.end());
            // Оставляем у child ровно T левых детей
            child->children.resize(T);
        }

        // Урезаем child до T-1 ключей/значений
        child->keys.resize(T - 1);
        child->values.resize(T - 1);

        // Вставляем медиану в родителя
        parent->keys.insert(parent->keys.begin() + idx, medianKey);
        parent->values.insert(parent->values.begin() + idx, medianValue);
        parent->children.insert(parent->children.begin() + idx + 1, newNode);
    }

    // Вставка в узел, который гарантированно не заполнен (меньше 2*T-1 ключей)
    void insertNonFull(Node* node, const K& key, const V& value) {
        if (node->isLeaf) {
            // Вставка в лист с сохранением порядка
            size_t i = 0;
            while (i < node->keys.size() && key > node->keys[i]) ++i;
            if (i < node->keys.size() && key == node->keys[i]) {
                node->values[i] = value;   // обновление существующего
                return;
            }
            node->keys.insert(node->keys.begin() + i, key);
            node->values.insert(node->values.begin() + i, value);
            ++count;
        }
        else {
            // Ищем дочерний узел
            size_t i = 0;
            while (i < node->keys.size() && key > node->keys[i]) ++i;
            // Если дочерний узел заполнен – разделяем его
            if (node->children[i]->keys.size() == 2 * T - 1) {
                splitChild(node, i, node->children[i]);
                // После разделения решаем, в какой из двух узлов спускаться
                if (key > node->keys[i]) ++i;
            }
            insertNonFull(node->children[i], key, value);
        }
    }

public:
    BTree() : root(new Node(true)) {}

    void insert(const K& key, const V& value) {
        if (root->keys.size() == 2 * T - 1) {
            // Корень заполнен – создаём новый корень и разделяем старый
            Node* newRoot = new Node(false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0, root);
            root = newRoot;
            insertNonFull(root, key, value);
        }
        else {
            insertNonFull(root, key, value);
        }
    }

    V* find(const K& key) {
        Node* node = root;
        while (node) {
            size_t i = 0;
            while (i < node->keys.size() && key > node->keys[i]) ++i;
            if (i < node->keys.size() && key == node->keys[i])
                return &node->values[i];
            if (node->isLeaf) break;
            node = node->children[i];
        }
        return nullptr;
    }

    size_t size() const { return count; }
};



void testBSTInsertFind() {
    BST<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    ASSERT_EQUAL(std::string("five"), *tree.find(5));
    ASSERT_EQUAL(std::string("three"), *tree.find(3));
    ASSERT_EQUAL(std::string("seven"), *tree.find(7));
    ASSERT_TRUE(tree.find(10) == nullptr);
}
void testBSTInorder() {
    BST<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    std::vector<int> keys;
    tree.inorder(keys);
    ASSERT_EQUAL(3, keys.size());
    ASSERT_EQUAL(3, keys[0]);
    ASSERT_EQUAL(5, keys[1]);
    ASSERT_EQUAL(7, keys[2]);
}
void testBSTRemoveLeaf() {
    BST<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.remove(3);
    ASSERT_TRUE(tree.find(3) == nullptr);
    ASSERT_EQUAL(1, tree.size()); // если добавим счётчик
}
void testBSTRemoveOneChild() {
    BST<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(2, "two");
    tree.remove(3);
    ASSERT_TRUE(tree.find(3) == nullptr);
    ASSERT_EQUAL(std::string("two"), *tree.find(2));
}
void testBSTRemoveTwoChildren() {
    BST<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(6, "six");
    tree.remove(5);
    ASSERT_TRUE(tree.find(5) == nullptr);
    ASSERT_EQUAL(std::string("six"), *tree.find(6)); // преемник
}

void testAVLInsertFind() {
    AVLTree<int, std::string> tree;
    tree.insert(10, "ten");
    tree.insert(20, "twenty");
    tree.insert(30, "thirty"); // RR вращение
    ASSERT_EQUAL(std::string("ten"), *tree.find(10));
    ASSERT_EQUAL(std::string("twenty"), *tree.find(20));
    ASSERT_EQUAL(std::string("thirty"), *tree.find(30));
    ASSERT_EQUAL(3, tree.size());
}
void testAVLBalance() {
    AVLTree<int, int> tree;
    for (int i = 0; i < 1000; ++i) tree.insert(i, i);
    // Высота AVL с 1000 элементами должна быть меньше 20 (теоретически <= 1.44*log2(1000) ~ 14.4)
    ASSERT_TRUE(tree.getHeight() < 20);
}

void testBTreeInsertFind() {
    BTree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    ASSERT_EQUAL(std::string("five"), *tree.find(5));
    ASSERT_EQUAL(std::string("three"), *tree.find(3));
    ASSERT_EQUAL(std::string("seven"), *tree.find(7));
    ASSERT_EQUAL(3, tree.size());
}
void testBTreeLargeInsert() {
    BTree<int, int> tree;
    for (int i = 0; i < 100; ++i) tree.insert(i, i);
    for (int i = 0; i < 100; ++i) {
        ASSERT_TRUE(tree.find(i) != nullptr);
    }
    ASSERT_EQUAL(100, tree.size());
}
