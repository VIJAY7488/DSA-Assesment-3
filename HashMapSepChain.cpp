#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <string>

using namespace std;

template <typename K, typename V>
class Entry {
public:
    K key;
    V value;
    int hash;

    Entry(K key, V value) : key(key), value(value), hash(hashFunction(key)) {}


    static int hashFunction(const K& key) {
        
        return std::hash<K>{}(key);
    }
};

template <typename K, typename V>
class HashMap {
private:
    int size;
    int capacity;
    vector<list<Entry<K, V>>> data;

public:
    HashMap() : size(0), capacity(10) {
        data.resize(capacity);
    }

    int getSize() const {
        return size;
    }

    void insert(const K& key, const V& value) {
        int index = abs(std::hash<K>{}(key) % capacity);
        for (auto& entry : data[index]) {
            if (entry.key == key) {
                entry.value = value;
                return;
            }
        }
        data[index].emplace_back(key, value);
        size++;
    }

    V get(const K& key) const {
        int index = abs(std::hash<K>{}(key) % capacity);
        for (const auto& entry : data[index]) {
            if (entry.key == key) {
                return entry.value;
            }
        }
        return V(); 
    }

    void remove(const K& key) {
        int index = abs(std::hash<K>{}(key) % capacity);
        auto& bucket = data[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                size--;
                return;
            }
        }
    }

    void display() const {
        for (const auto& bucket : data) {
            for (const auto& entry : bucket) {
                cout << entry.key << " " << entry.value << endl;
            }
        }
    }
};

int main() {
    HashMap<string, int> map;
    map.insert("1", 1);
    map.insert("2", 7);
    map.insert("3", 3);
    map.insert("1", 0);
    map.insert("ankit", 0);
    map.insert("raj", 0);
    map.insert("raj", 1);
    map.insert("rj", 0);
    map.insert("j", 0);

    map.display();
    int value = map.get("2");
    cout << value << endl;
    cout << endl;

    map.remove("raj");

    cout << map.getSize() << endl;

    map.display();

    return 0;
}
