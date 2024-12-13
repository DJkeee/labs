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
    { a < b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
};

template<typename K, typename V>
struct Node {
    KeyValue<K, V> data;
    Node* left;
    Node* right;
    Node* parent;
    Color color;
    Node(K key, V value): data{key, value}, left(nullptr),
                                   right(nullptr), parent(nullptr), color(RED) {
    }
};

template<typename K, typename V> requires Comparator<K>
class RedBlackTree {
private:
    Node<K, V>* root;

    Node<K, V>* deleteHelper(K key) {
        Node<K, V>* current = root;
        Node<K, V>* parent = nullptr;
        Node<K, V>* nodeToDelete = nullptr;

        while (current != nullptr) {
            if (key == current->key) {
                nodeToDelete = current;
                break;
            } else if (key < current->key) {
                parent = current;
                current = current->left;
            } else {
                parent = current;
                current = current->right;
            }
        }

        if (nodeToDelete == nullptr) {
            return root;
        }

        Node<K, V>* child = nullptr;
        if (nodeToDelete->left == nullptr || nodeToDelete->right == nullptr) {
            child = (nodeToDelete->left != nullptr) ? nodeToDelete->left : nodeToDelete->right;
        } else {
            Node<K, V>* successor = nodeToDelete->right;
            Node<K, V>* successorParent = nodeToDelete;

            while (successor->left != nullptr) {
                successorParent = successor;
                successor = successor->left;
            }

            nodeToDelete->key = successor->key;
            nodeToDelete->value = successor->value;

            child = successor->right;

            if (successorParent != nodeToDelete) {
                successorParent->left = child;
            } else {
                successorParent->right = child;
            }

            nodeToDelete = successor;
        }

        if (parent == nullptr) {
            root = child;
        } else if (nodeToDelete == parent->left) {
            parent->left = child;
        } else {
            parent->right = child;
        }

        delete nodeToDelete;
        return root;
    }

    Node<K, V>* searchAndGetNodeHelper(K key) {
        Node<K, V>* current = root;
        while (current != nullptr) {
            if (key == current->data.key) {
                return current;
            }
            if (key < current->data.key) {
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

    void inOrderCopy(Node<K, V>* node) {
        if (node != nullptr) {
            inOrderCopy(node->left);
            auto* newNode = new Node<K, V>(node->key, node->value);
            newNode->color = node->color;
            insertHelper(newNode);
            inOrderCopy(node->right);
        }
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

    template<typename Func>
    void inorderHelper(Node<K, V>* node, std::function<Func>& func) {
        if (!node) return;
        inorderHelper(node->left);
        func(node->data);
        inorderHelper(node->right);
    }

    void postOrderHelper(Node<K,V>* node, const std::function<void(Node<K,V>*)>& func) {
        if (!node) return;
        postOrderHelper(node->left, func);
        postOrderHelper(node->right, func);
        func(node); // Применяем функцию к узлу
    }

    template<typename Func>
    void preOrderHelper(Node<K, V>* node, std::function<Func>& func) {
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

    ~RedBlackTree() {
      //  postOrder([this](Node<K,V>* node) {
        //    delete node; // Освобождаем память
    }

    RedBlackTree(const RedBlackTree& other): root(nullptr) {
        if (other.root != nullptr) {
            inOrderCopy(other.root);
        }
    }

    void postOrder(const std::function<void(Node<K, V>*)> func) {
        postOrderHelper(root, func);
    }

    template<typename Func>
    void preOrder(std::function<Func>& func) {
        preOrderHelper(root, func);
    }

    template<typename Func>
    void inOrder(std::function<Func>& func) {
        inorderHelper(root, func);
    }

    bool searchByKey(K key) {
        return searchAndGetNodeHelper(key)->data.val != nullptr;
    }

    V getByKey(K key) {
        return searchAndGetNodeHelper(key)->data.val;
    }

    void insert(K key, V val) {
        Node<K, V> node = new Node<K, V>((key, val));
        insertHelper(node);
    }

    void print() {
        inorderHelper(root, [](Node<K, V>* node) {
            std::cout << "Key: " << node->data.key << ", Value: " << node->data.val << std::endl;
        });
    }

    void deleteByKey(K key) {
        deleteHelper(key);
    }
};
