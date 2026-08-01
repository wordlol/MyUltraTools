#pragma once
//12
/*
 * Формальная постановка: для заданной строки text[0..n-1] и образа pattern[0..m-1]
 * найти все позиции i, такие что text[i..i+m-1] == pattern.
 *
 * Классификация:
 * - Прямые алгоритмы: наивный (сравнение в лоб), O((n-m+1)*m) худший случай.
 * - Улучшенные: Кнут-Моррис-Пратт (КМП), Бойер-Мур, Рабин-Карп.
 *   У них линейная или сублинейная сложность за счёт предобработки.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ---------- ПРЯМОЙ (НАИВНЫЙ) АЛГОРИТМ ----------
// Сложность: время O((n-m+1)*m), память O(1).
// Для каждой позиции i в тексте проверяем совпадение всех m символов.
vector<size_t> naiveSearch(const string& text, const string& pattern) {
    vector<size_t> pos;
    size_t n = text.size(), m = pattern.size();
    if (m == 0 || m > n) return pos;   // пустой образ или длиннее текста

    for (size_t i = 0; i <= n - m; ++i) {
        bool match = true;
        for (size_t j = 0; j < m; ++j) {
            if (text[i + j] != pattern[j]) {
                match = false;
                break;
            }
        }
        if (match) pos.push_back(i);
    }
    return pos;
}

// ---------- УЛУЧШЕННЫЙ АЛГОРИТМ КМП ----------
// Сложность: время O(n + m), память O(m) для префикс-функции (LPS).
// Использует предобработку образа для пропуска заведомо несовпадающих сдвигов.

// Вычисление LPS (Longest Proper Prefix which is also Suffix).
// lps[i] = длина наибольшего собственного префикса pattern[0..i-1], 
//          который одновременно является суффиксом pattern[0..i].
vector<size_t> computeLPS(const string& pattern) {
    size_t m = pattern.size();
    vector<size_t> lps(m, 0);
    size_t len = 0; // длина предыдущего наибольшего префикса-суффикса
    size_t i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            ++len;
            lps[i] = len;
            ++i;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];   // пытаемся найти более короткий префикс-суффикс
            }
            else {
                lps[i] = 0;
                ++i;
            }
        }
    }
    return lps;
}

vector<size_t> KMPSearch(const string& text, const string& pattern) {
    vector<size_t> pos;
    size_t n = text.size(), m = pattern.size();
    if (m == 0 || m > n) return pos;

    vector<size_t> lps = computeLPS(pattern);
    size_t i = 0; // индекс в text
    size_t j = 0; // индекс в pattern

    while (i < n) {
        if (pattern[j] == text[i]) {
            ++i; ++j;
        }
        if (j == m) {               // найдено полное совпадение
            pos.push_back(i - j);
            j = lps[j - 1];         // продолжаем поиск следующих вхождений
        }
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];     // сдвигаем образ, не трогая i
            }
            else {
                ++i;
            }
        }
    }
    return pos;
}


void R12()
{
    string text = "ABABABCABABABCABABABC";
    string pattern = "ABABABC";

    auto resNaive = naiveSearch(text, pattern);
    auto resKMP = KMPSearch(text, pattern);

    cout << "Наивный поиск: ";
    for (size_t p : resNaive) cout << p << " ";
    cout << "\nКМП:          ";
    for (size_t p : resKMP) cout << p << " ";
    cout << endl;

    // Простая проверка: результаты должны совпадать
    if (resNaive == resKMP) cout << "Результаты совпадают.\n";
}