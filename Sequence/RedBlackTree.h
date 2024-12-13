//
// Created by dmitry on 12/12/24.
//

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include <functional>
#include <iostream>

enum Color { RED, BLACK };

template<typename T>
concept Comparator = requires(T a, T b)
{
    { a < b } -> std::convertible_to<std::strong_ordering>;
    { a > b } -> std::convertible_to<std::strong_ordering>;
};

template<typename T> requires Comparator
struct Node<T> {
    T data;
    Node* left;
    Node* right;
    Node* parent;
    Color color;

    explicit Node(T data): data(data), left(nullptr),
                           right(nullptr), parent(nullptr), color(RED) {
    }
};

template<typename T>
class RedBlackTree {
private:
    Node<T>* root;

    void inorderHelper(Node<T>* node, std::function<void(T)>& func) {
        if (!node) return;
        inorderHelper(node->left);
        func(node->data);
        inorderHelper(node->right);
    }

    void postOrderHelper(Node<T>* node, std::function<void(T)>& func) {
        if (!node) return;
        postOrderHelper(node->left, func);
        postOrderHelper(node->right, func);
        func(node->data);
    }

    void preOrderHelper(Node<T>* node, std::function<void(T)>& func) {
        if (!node) return;
        func(node->data);
        preOrderHelper(node->left, func);
        preOrderHelper(node->right, func);
    }

    void rotateLeft(Node<T>* node) {
        if (!node || !node->left) return;

        Node<T>* right = node->right;
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

    void rotateRight(Node<T>* node) {
        // NOLINT(*-non-const-parameter)
        if (!node || !node - right) return;

        Node<T>* left = node->left;
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
    RedBlackTree()
        : root(nullptr) {
    }

    void postOrder(std::function<void(T)>& func) {
        postOrderHelper(root, func);
    }

    void preOrder(std::function<void(T)>& func) {
        preOrderHelper(root, func);
    }

    void inOrder(std::function<void(T)>& func) {
        inorderHelper(root, func);
    }
};
#endif //REDBLACKTREE_H
