#include <iostream>
#include <algorithm> 

using namespace std;

class Node {
public:
    int value;
    int height;
    int balanceFactor;
    Node* left;
    Node* right;

    Node(int value) : value(value), height(0), balanceFactor(0), left(nullptr), right(nullptr) {}
};

class AvlTree {
private:
    int nodesCount;
    Node* root;

    Node* insert(Node* node, int target) {
        if (node == nullptr) {
            return new Node(target);
        }

        if (target > node->value) {
            node->right = insert(node->right, target);
        } else {
            node->left = insert(node->left, target);
        }

        update(node);
        return balance(node);
    }

    void update(Node* node) {
        int leftHeight = (node->left == nullptr) ? -1 : node->left->height;
        int rightHeight = (node->right == nullptr) ? -1 : node->right->height;

        node->height = 1 + max(leftHeight, rightHeight);
        node->balanceFactor = rightHeight - leftHeight;
    }

    Node* balance(Node* node) {
        if (node->balanceFactor == 2) {
            if (node->right->balanceFactor >= 0) {
                return rightRightCase(node);
            } else {
                return rightLeftCase(node);
            }
        } else if (node->balanceFactor == -2) {
            if (node->left->balanceFactor <= 0) {
                return leftLeftCase(node);
            } else {
                return leftRightCase(node);
            }
        }
        return node;
    }

    Node* leftLeftCase(Node* node) {
        return rotateRight(node);
    }

    Node* leftRightCase(Node* node) {
        node->left = rotateLeft(node->left);
        return leftLeftCase(node);
    }

    Node* rightRightCase(Node* node) {
        return rotateLeft(node);
    }

    Node* rightLeftCase(Node* node) {
        node->right = rotateRight(node->right);
        return rightRightCase(node);
    }

    Node* rotateRight(Node* node) {
        Node* B = node->left;
        node->left = B->right;
        B->right = node;

        update(node);
        update(B);
        return B;
    }

    Node* rotateLeft(Node* node) {
        Node* B = node->right;
        node->right = B->left;
        B->left = node;

        update(node);
        update(B);
        return B;
    }

    Node* remove(Node* node, int target) {
        if (node == nullptr) {
            return nullptr;
        }

        if (target == node->value) {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            } else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            } else {
                Node* successor = node->left;
                while (successor->right != nullptr) {
                    successor = successor->right;
                }

                node->value = successor->value;
                node->left = remove(node->left, successor->value);
            }
        } else if (target > node->value) {
            node->right = remove(node->right, target);
        } else {
            node->left = remove(node->left, target);
        }

        update(node);
        return balance(node);
    }

    bool contains(Node* node, int target) const {
        if (node == nullptr) {
            return false;
        }

        if (node->value == target) {
            return true;
        }

        if (target > node->value) {
            return contains(node->right, target);
        } else {
            return contains(node->left, target);
        }
    }

    void inorder(Node* node) const {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->value << " ";
            inorder(node->right);
        }
    }

public:
    AvlTree() : nodesCount(0), root(nullptr) {}

    ~AvlTree() {
        
        destroyTree(root);
    }

    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    bool find(int value) const {
        return contains(root, value);
    }

    bool insert(int value) {
        if (find(value)) {
            return false;
        } else {
            root = insert(root, value);
            nodesCount++;
            return true;
        }
    }

    bool remove(int value) {
        if (!find(value)) {
            return false;
        } else {
            root = remove(root, value);
            nodesCount--;
            return true;
        }
    }

    int size() const {
        return nodesCount;
    }

    Node* getRoot() const {
        return root;
    }

    void inorder() const {
        inorder(root);
        cout << endl;
    }
};

int main() {
    AvlTree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(17);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    tree.insert(11);
    tree.insert(13);
    tree.insert(16);
    tree.insert(18);

    cout << "Size: " << tree.size() << endl;
    cout << "Root: " << tree.getRoot()->value << endl;

    tree.inorder();

    return 0;
}
