//
// Created by dmitry on 12/12/24.
//

#include <functional>
#include <iostream>

enum Color { RED, BLACK };

template<typename Key, typename Val>
struct KeyValue {
    Key key;
    Val val;

public:
    bool operator<(const KeyValue& other) const {
        return key < other.key;
    }

    bool operator ==(const KeyValue& other) const {
        return key == other.key;
    }

    bool operator !=(const KeyValue& other) const {
        return key != other.key;
    }

    bool operator >(const KeyValue& other) const {
        return key > other.val;
    }
};

template<typename T>
concept Comparator = requires(T a, T b)
{
    { a < b } -> std::convertible_to<std::strong_ordering>;
    { a > b } -> std::convertible_to<std::strong_ordering>;
};

template<typename K, typename V> requires Comparator<K>
struct Node {
    KeyValue<K, V> data;
    Node* left;
    Node* right;
    Node* parent;
    Color color;

    explicit Node(K key, V value): data{key, value}, left(nullptr),
                                   right(nullptr), parent(nullptr), color(RED) {
    }
};

template<typename K, typename V>
class RedBlackTree {
private:
    Node<K, V>* root;

    Node<K, V>* searchAndGetNodeHelper(Node<K, V>* node) {
        Node<K, V>* current = root;
        while (current != nullptr) {
            if (node->key == current->data.key) {
                return current;
            }
            if (node->key < current->data.key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return nullptr;
    }

    void insertHelper(Node<K, V>* node) {
        if (!root) {
            root = node;
            root->color = BLACK;
            return;
        }
        Node<K, V>* parent = searchAndGetHelper(root);
        node->parent = parent;
        balanceTree(node);
    }

    void balanceTree(Node<K, V>* node) {
        while (node != root && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                Node<K, V> temp = node->parent->parent->data;
                if (temp && temp->color == RED) {
                    node->parent->color = BLACK;
                    temp->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }

                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateRight(node->parent->parent);
                }
            } else {
                Node<K, V>* temp = node->parent->parent->left;
                if (temp && temp->color == RED) {
                    node->parent->color = BLACK;
                    temp->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateLeft(node->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void inorderHelper(Node<K, V>* node, std::function<void(KeyValue<K, V>)>& func) {
        if (!node) return;
        inorderHelper(node->left);
        func(node->data);
        inorderHelper(node->right);
    }

    void postOrderHelper(Node<K, V>* node, std::function<KeyValue<K, V> >& func) {
        if (!node) return;
        postOrderHelper(node->left, func);
        postOrderHelper(node->right, func);
        func(node->data);
    }

    void preOrderHelper(Node<K, V>* node, std::function<KeyValue<K, V> >& func) {
        if (!node) return;
        func(node->data);
        preOrderHelper(node->left, func);
        preOrderHelper(node->right, func);
    }

    void rotateLeft(Node<K, V>* node) {
        if (!node || !node->left) return;

        Node<K, V>* right = node->right;
        node->right = right->left;

        if (node->right) {
            node->right->parent = node;
        }
        right->parent = node->parent;

        if (!node->parent) {
            root = right;
        } else if (node->parent->left == node) {
            node->parent->left = right;
        } else {
            node->parent->right = right;
        }
        right->left = node;
        node->parent = right;
    }

    void rotateRight(Node<K, V>* node) {
        if (!node || !node->right) return;

        Node<K, V>* left = node->left;
        node->left = left->right;

        if (node->left) {
            node->left->parent = node;
        }

        left->parent = node->parent;

        if (!node->parent) {
            root = node;
        } else if (node->parent->left == node) {
            node->parent->left = left;
        } else {
            node->parent->right = left;
        }
        left->right = node;
        node->parent = left;
    }

public:
    RedBlackTree(): root(nullptr) {
        root->color = BLACK;
    }

    void postOrder(std::function<void(K)>& func) {
        postOrderHelper(root, func);
    }

    void preOrder(std::function<void(K)>& func) {
        preOrderHelper(root, func);
    }

    void inOrder(std::function<void(K)>& func) {
        inorderHelper(root, func);
    }

    bool searchByKey(K key) {
        return searchAndGetNodeHelper(key);
    }

    V getByKey(K key) {
        return searchAndGetNodeHelper(key);
    }
};
