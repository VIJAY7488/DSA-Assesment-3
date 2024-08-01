#include <iostream>
#include <unordered_map>

using namespace std;

class DLL {
public:
    class Node {
    public:
        int key;
        int val;
        Node* next;
        Node* prev;

        Node(int key, int val) : key(key), val(val), next(nullptr), prev(nullptr) {}
    };

    DLL() : head(nullptr), tail(nullptr) {}

    void append(Node* node) {
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    void moveToEnd(Node* node) {
        if (node == nullptr || head == nullptr || node == tail) {
            return;
        }

        if (node == head) {
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
        } else {
            node->prev->next = node->next;
            if (node->next != nullptr) {
                node->next->prev = node->prev;
            }
        }

        node->next = nullptr;
        node->prev = tail;
        if (tail != nullptr) {
            tail->next = node;
        }
        tail = node;

        if (head == nullptr) {
            head = node;
        }
    }

    void deleteFront() {
        if (head == nullptr) {
            return;
        }

        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
    }

    Node* head;
    Node* tail;
};

class LRUCache {
private:
    DLL dll;
    unordered_map<int, DLL::Node*> map;
    int cap;

public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        if (map.find(key) == map.end()) {
            return -1;
        }
        DLL::Node* node = map[key];
        dll.moveToEnd(node);
        return node->val;
    }

    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            DLL::Node* node = map[key];
            node->val = value;
            dll.moveToEnd(node);
        } else {
            if (map.size() >= cap) {
                DLL::Node* nodeToRemove = dll.head;
                dll.deleteFront();
                map.erase(nodeToRemove->key);
                delete nodeToRemove;
            }
            DLL::Node* node = new DLL::Node(key, value);
            dll.append(node);
            map[key] = node;
        }
    }
};

int main() {
    LRUCache cache(2); 

    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl; 
    cache.put(3, 3); 
    cout << cache.get(2) << endl; 
    cache.put(4, 4); 
    cout << cache.get(1) << endl; 
    cout << cache.get(3) << endl; 
    cout << cache.get(4) << endl; 

    return 0;
}
