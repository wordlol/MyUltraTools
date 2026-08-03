#pragma once
/*
 * 16. Сжатие данных без потерь: алгоритм Хаффмана.
 *
 * Идея: более часто встречающимся символам присваиваются короткие коды,
 * редким — длинные. Это оптимальное префиксное кодирование.
 *
 * Шаги:
 * 1. Подсчет частот символов.
 * 2. Построение дерева Хаффмана с помощью мин-кучи.
 * 3. Генерация кодов обходом дерева (лево – '0', право – '1').
 * 4. Кодирование и декодирование.
 *
 * Сложность: O(N + K log K), где N – размер текста, K – количество уникальных символов.
 * Память: O(K) для дерева и таблицы кодов.
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <bitset>
#include <locale>
#include <memory>
using namespace std;

// Узел дерева Хаффмана
struct HuffmanNode {
    char ch;
    int freq;
    shared_ptr<HuffmanNode> left, right;
    HuffmanNode(char c, int f) : ch(c), freq(f) {}
    HuffmanNode(int f, shared_ptr<HuffmanNode> l, shared_ptr<HuffmanNode> r)
        : ch('\0'), freq(f), left(l), right(r) {
    }
};

// Компаратор для мин-кучи (сравниваем по частоте)
struct CompareNode {
    bool operator()(const shared_ptr<HuffmanNode>& a, const shared_ptr<HuffmanNode>& b) const {
        return a->freq > b->freq; // мин-куча
    }
};

// Рекурсивное построение таблицы кодов
void buildCodes(const shared_ptr<HuffmanNode>& node, const string& code,
    unordered_map<char, string>& huffCode) {
    if (!node) return;
    if (!node->left && !node->right) { // лист
        huffCode[node->ch] = code;
    }
    buildCodes(node->left, code + "0", huffCode);
    buildCodes(node->right, code + "1", huffCode);
}

// Основная функция кодирования Хаффмана
// Возвращает закодированную строку и таблицу кодов.
pair<string, unordered_map<char, string>> huffmanEncode(const string& text) {
    if (text.empty()) return {};

    // 1. Подсчет частот
    unordered_map<char, int> freq;
    for (char c : text) freq[c]++;

    // 2. Построение мин-кучи
    priority_queue<shared_ptr<HuffmanNode>, vector<shared_ptr<HuffmanNode>>, CompareNode> pq;
    for (auto& [ch, f] : freq) {
        pq.push(make_shared<HuffmanNode>(ch, f));
    }

    // 3. Построение дерева
    while (pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();
        auto parent = make_shared<HuffmanNode>(left->freq + right->freq, left, right);
        pq.push(parent);
    }
    auto root = pq.top();

    // 4. Генерация кодов
    unordered_map<char, string> huffCode;
    buildCodes(root, "", huffCode);

    // 5. Кодирование текста
    string encoded;
    for (char c : text) encoded += huffCode[c];

    return { encoded, huffCode };
}

// Декодирование строки по дереву Хаффмана
string huffmanDecode(const string& encoded, const shared_ptr<HuffmanNode>& root) {
    string decoded;
    auto current = root;
    for (char bit : encoded) {
        if (bit == '0') current = current->left;
        else current = current->right;

        if (!current->left && !current->right) { // лист
            decoded += current->ch;
            current = root;
        }
    }
    return decoded;
}

void R16()
{
    setlocale(LC_ALL, "");
    string text = "ABBCCCDDDDEEEEE"; // пример строки с разными частотами
    cout << "Исходный текст: " << text << endl;

    auto [encoded, codes] = huffmanEncode(text);
    cout << "\nТаблица кодов Хаффмана:\n";
    for (auto& [ch, code] : codes) {
        cout << "  '" << ch << "' : " << code << endl;
    }
    cout << "\nЗакодированная строка: " << encoded << endl;

    // Для декодирования нужно сохранить дерево или таблицу кодов.
    // Здесь для примера восстановим дерево из таблицы (но проще передать дерево).
    // Просто покажем, что декодирование возможно, если есть дерево.

    // Построим дерево повторно (в реальности его нужно сохранять вместе с данными)
    unordered_map<char, int> freq;
    for (char c : text) freq[c]++;
    priority_queue<shared_ptr<HuffmanNode>, vector<shared_ptr<HuffmanNode>>, CompareNode> pq;
    for (auto& [ch, f] : freq) pq.push(make_shared<HuffmanNode>(ch, f));
    while (pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();
        pq.push(make_shared<HuffmanNode>(left->freq + right->freq, left, right));
    }
    auto root = pq.top();

    string decoded = huffmanDecode(encoded, root);
    cout << "Декодированный текст: " << decoded << endl;
    if (text == decoded) cout << "Сжатие без потерь: успех!" << endl;

}
