#include <iostream>

class HashSet {
private:
    static const int TABLE_SIZE = 10;

    class Node {
    public:
        int data;
        Node* next;

        Node(int val) : data(val), next(nullptr) {}
    };

    Node* table[TABLE_SIZE];

    int hash(int key) {
        return key % TABLE_SIZE;
    }

public:
    HashSet() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;
        }
    }

    ~HashSet() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    void remove(int key) {
        int index = hash(key);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current != nullptr && current->data != key) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            return;
        }

        if (prev == nullptr) {
            table[index] = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;
    }

    void insert(int key) {
        int index = hash(key);

        if (!contains(key)) {
            Node* newNode = new Node(key);
            newNode->next = table[index];
            table[index] = newNode;
        }
    }

    bool contains(int key) {
        int index = hash(key);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->data == key) {
                return true;
            }
            current = current->next;
        }

        return false;
    }

    int size() {
        int count = 0;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = table[i];
            while (current != nullptr) {
                ++count;
                current = current->next;
            }
        }
        return count;
    }

    bool isEmpty() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i] != nullptr) {
                return false;
            }
        }
        return true;
    }

    void print() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = table[i];
            std::cout << "Bucket " << i << ": ";
            while (current != nullptr) {
                std::cout << current->data << " ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    HashSet set;

    set.insert(0);
    set.insert(7);
    set.insert(30);
    set.insert(45);
    set.insert(46);
    set.insert(57);

    std::cout << "Contains 7 " << (set.contains(7) ? "true" : "false") << std::endl;

    set.remove(7);
    std::cout << "Contains 7 " << (set.contains(7) ? "true" : "false") << std::endl;

    std::cout << "Size " << set.size() << std::endl;

    std::cout << "Empty? " << (set.isEmpty() ? "true" : "false") << std::endl;

    set.print();

    return 0;
}
