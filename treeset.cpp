#include <iostream>

template <typename T>
class TreeSet {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* root, const T& value) {
        if (root == nullptr) {
            return new Node(value);
        }

        if (value < root->data) {
            root->left = insert(root->left, value);
        } else if (value > root->data) {
            root->right = insert(root->right, value);
        }

        return root;
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* remove(Node* root, const T& value) {
        if (root == nullptr) {
            return root;
        }

        if (value < root->data) {
            root->left = remove(root->left, value);
        } else if (value > root->data) {
            root->right = remove(root->right, value);
        } else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = findMin(root->right);

            root->data = temp->data;

            root->right = remove(root->right, temp->data);
        }

        return root;
    }

    void inorderTraversal(Node* root) {
        if (root != nullptr) {
            inorderTraversal(root->left);
            std::cout << root->data << " ";
            inorderTraversal(root->right);
        }
    }

public:
    TreeSet() : root(nullptr) {}

    void insert(const T& value) {
        root = insert(root, value);
    }

    void remove(const T& value) {
        root = remove(root, value);
    }

    bool find(const T& value) const {
        Node* current = root;
        while (current != nullptr) {
            if (value == current->data) {
                return true;
            } else if (value < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    }

    void print() {
        inorderTraversal(root);
        std::cout << std::endl;
    }
};

int main() {
    TreeSet<int> treeSet;

    treeSet.insert(1);
    treeSet.insert(2);
    treeSet.insert(3);
    treeSet.insert(4);
    treeSet.insert(5);

    std::cout << "Tree ";
    treeSet.print();

    int s_num = 5;
    if (treeSet.find(s_num)) {
        std::cout << s_num << std::endl;
    } else {
        std::cout << "not find" << std::endl;
    }

    int s_num_ = 8;
    if (treeSet.find(s_num_)) {
        std::cout << s_num << std::endl;
    } else {
        std::cout << "not find" << std::endl;
    }

    int r_num = 2;
    treeSet.remove(r_num);
    treeSet.print();

    return 0;
}
