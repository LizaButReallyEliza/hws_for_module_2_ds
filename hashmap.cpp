#include <iostream>
#include <list>

template <typename K, typename V>
struct KeyValuePair {
    K key;
    V value;

    KeyValuePair(const K& k, const V& v) : key(k), value(v) {}
};

template <typename K, typename V>
class HashMap {
private:
    using Bucket = std::list<KeyValuePair<K, V>>;

    Bucket** table;
    size_t capacity;
    size_t size;

    size_t hash(const K& key) const {
        return std::hash<K>{}(key) % capacity;
    }

public:
    HashMap(size_t initialCapacity = 16) : capacity(initialCapacity), size(0) {
        table = new Bucket*[capacity]();
    }

    ~HashMap() {
        for (size_t i = 0; i < capacity; ++i) {
            delete table[i];
        }
        delete[] table;
    }

public:
    void rehash(size_t newCapacity) {
        Bucket** newTable = new Bucket*[newCapacity]();
        for (size_t i = 0; i < capacity; ++i) {
            if (table[i] != nullptr) {
                for (auto& pair : *table[i]) {
                    size_t newIndex = std::hash<K>{}(pair.key) % newCapacity;
                    if (newTable[newIndex] == nullptr) {
                        newTable[newIndex] = new Bucket;
                    }
                    newTable[newIndex]->push_back(pair);
                }
                delete table[i];
            }
        }

        delete[] table;
        table = newTable;
        capacity = newCapacity;
    }

    void insert(const K& key, const V& value) {
        size_t index = hash(key);

        if (table[index] == nullptr) {
            table[index] = new Bucket;
        }

        table[index]->push_back(KeyValuePair<K, V>(key, value));
        size++;

        if (size >= capacity) {
            size_t newCapacity = capacity * 2;
            rehash(newCapacity);
        }
    }

    V* get(const K& key) {
        size_t index = hash(key);
        if (table[index] != nullptr) {
            for (auto& pair : *table[index]) {
                if (pair.key == key) {
                    return &pair.value;
                }
            }
        }
        return nullptr;
    }

    void remove(const K& key) {
        size_t index = hash(key);
        if (table[index] != nullptr) {
            auto& bucket = *table[index];
            for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                if (it->key == key) {
                    bucket.erase(it);
                    size--;
                    break;
                }
            }
        }
    }

    bool contains(const K& key) const {
        size_t index = hash(key);
        if (table[index] != nullptr) {
            for (const auto& pair : *table[index]) {
                if (pair.key == key) {
                    return true;
                }
            }
        }
        return false;
    }

    bool empty() const {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }
};

int main() {
    HashMap<int, std::string> map;

    map.insert(19, "age");
    map.insert(2004, "Birth year");
    map.insert(2023, "This year");

    std::cout << "Size " << map.getSize() << std::endl;

    std::string* val = map.get(20);
    if (val != nullptr) {
        std::cout << "Value " << *val << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    map.remove(20);

    std::cout << "Size " << map.getSize() << std::endl;

    bool containsKey = map.contains(20);
    std::cout << "Contains " << (containsKey ? "Yes" : "No") << std::endl;

    return 0;
}
