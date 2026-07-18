#pragma once
#include "Tamplates.h"
//8
//Абстрактные типы данных в программировании.Ассоциативные массивы
//и списки.Определить их словесно или с использованием схем, основные
//операции над ними.Показать их вычислительную сложность.

//LinkedList
template <typename T>
struct Node {
    T data;
    Node* next;
    Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    size_t sz = 0;
public:
    ~LinkedList();
    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    Node<T>* find(const T& value) const;
    bool contains(const T& value) const { return find(value) != nullptr; }
    size_t size() const { return sz; }
    bool empty() const { return sz == 0; }
};

template <typename T>
void LinkedList<T>::push_front(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    newNode->next = head;
    head = newNode;
    if (!tail) tail = head;
    ++sz;
}
template <typename T>
Node<T>* LinkedList<T>::find(const T& value) const {
    Node<T>* curr = head;
    while (curr) {
        if (curr->data == value) return curr;
        curr = curr->next;
    }
    return nullptr;
}
template <typename T>
LinkedList<T>::~LinkedList() {
    while (head) {
        Node<T>* tmp = head;
        head = head->next;
        delete tmp;
    }
}
template <typename T>
void LinkedList<T>::push_back(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    ++sz;
}
template <typename T>
void LinkedList<T>::pop_front() {
    if (!head) throw std::runtime_error("List is empty");
    Node<T>* tmp = head;
    head = head->next;
    delete tmp;
    if (!head) tail = nullptr;
    --sz;
}
template <typename T>
void LinkedList<T>::pop_back() {
    if (!head) throw std::runtime_error("List is empty");
    if (head == tail) {
        delete head;
        head = tail = nullptr;
        sz = 0;
        return;
    }
    Node<T>* curr = head;
    while (curr->next != tail) {
        curr = curr->next;
    }
    delete tail;
    tail = curr;
    tail->next = nullptr;
    --sz;
}


//HashMap
template <typename K, typename V>
class HashMap {
    static constexpr size_t DEFAULT_BUCKETS = 16;
    std::vector<std::list<std::pair<const K, V>>> buckets;
    size_t count = 0;
    size_t hash(const K& key) const { return std::hash<K>{}(key) % buckets.size(); }
public:
    HashMap(size_t bucketCount = DEFAULT_BUCKETS)
        : buckets(bucketCount) {
    }

    void insert(const K& key, const V& value);
    V* find(const K& key);
    void remove(const K& key);
    size_t size() const { return count; }
};

template <typename K, typename V>
void HashMap<K, V>::insert(const K& key, const V& value) {
    size_t idx = hash(key);
    // Проверим, нет ли уже такого ключа, если есть – перезапишем
    for (auto& [k, v] : buckets[idx]) {
        if (k == key) {
            v = value;
            return;
        }
    }
    buckets[idx].emplace_back(key, value);
    ++count;
}
template <typename K, typename V>
V* HashMap<K, V>::find(const K& key) {
    size_t idx = hash(key);
    for (auto& [k, v] : buckets[idx]) {
        if (k == key) return &v;
    }
    return nullptr;
}
template <typename K, typename V>
void HashMap<K, V>::remove(const K& key) {
    size_t idx = hash(key);
    auto& bucket = buckets[idx];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            bucket.erase(it);
            --count;
            return;
        }
    }
    throw std::runtime_error("Key not found");
}



void testLinkedListPushFront() {
    LinkedList<int> list;
    list.push_front(10);
    ASSERT_TRUE(list.contains(10));
    ASSERT_EQUAL(1, list.size());
    list.push_front(20);
    ASSERT_TRUE(list.contains(10));
    ASSERT_TRUE(list.contains(20));
    ASSERT_EQUAL(2, list.size());
}
void testLinkedListPushBack() {
    LinkedList<int> list;
    list.push_back(30);
    ASSERT_TRUE(list.contains(30));
    ASSERT_EQUAL(1, list.size());
    list.push_back(40);
    ASSERT_TRUE(list.contains(30) && list.contains(40));
    ASSERT_EQUAL(2, list.size());
}
void testLinkedListPopFront() {
    LinkedList<int> list;
    list.push_front(10);
    list.push_front(20);
    list.pop_front();
    ASSERT_TRUE(list.contains(10));
    ASSERT_FALSE(list.contains(20));
    ASSERT_EQUAL(1, list.size());
}
void testLinkedListPopBack() {
    LinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.pop_back();
    ASSERT_TRUE(list.contains(10));
    ASSERT_FALSE(list.contains(20));
    ASSERT_EQUAL(1, list.size());
}
void testLinkedListPopEmpty() {
    LinkedList<int> list;
    ASSERT_THROWS(list.pop_front());
}

void testHashMapInsertFind() {
    HashMap<std::string, int> map;
    map.insert("apple", 5);
    int* val = map.find("apple");
    ASSERT_TRUE(val != nullptr);
    ASSERT_EQUAL(5, *val);
    ASSERT_EQUAL(1, map.size());
}
void testHashMapOverwrite() {
    HashMap<int, std::string> map;
    map.insert(1, "one");
    map.insert(1, "uno");
    ASSERT_EQUAL("uno", *map.find(1));
    ASSERT_EQUAL(1, map.size());
}
void testHashMapRemove() {
    HashMap<int, std::string> map;
    map.insert(1, "one");
    map.remove(1);
    ASSERT_TRUE(map.find(1) == nullptr);
    ASSERT_EQUAL(0, map.size());
}