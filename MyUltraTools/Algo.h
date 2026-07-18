#pragma once
#include "Trees.h"
#include <limits>
//10
//Понятие рекурсии в программировании.Рекурсивные и нерекурсивные
//алгоритмы.Условия окончания работы.Привести примеры рекурсивного и
//нерекурсивного алгоритмов, соответственно(словесно или с использованием
//схем).Показать их вычислительную сложность.


unsigned long long factorial_recursive(int n) {
    if (n < 0) throw std::invalid_argument("Negative argument");
    if (n <= 1) return 1;
    return n * factorial_recursive(n - 1);
}
unsigned long long factorial_tail(int n, unsigned long long acc = 1) {
    if (n < 0) throw std::invalid_argument("Negative argument");
    if (n <= 1) return acc;
    return factorial_tail(n - 1, acc * n);
}
unsigned long long factorial_iterative(int n) {
    if (n < 0) throw std::invalid_argument("Negative argument");
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}


unsigned long long fib_recursive(int n) {
    if (n < 0) throw std::invalid_argument("Negative index");
    if (n <= 1) return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}
unsigned long long fib_memo(int n, std::vector<unsigned long long>& cache) {
    if (n < 0) throw std::invalid_argument("Negative index");
    if (n <= 1) return n;
    if (cache[n] != ULLONG_MAX) return cache[n];   // ULLONG_MAX – маркер "не вычислено"
    cache[n] = fib_memo(n - 1, cache) + fib_memo(n - 2, cache);
    return cache[n];
}
unsigned long long fib_iterative(int n) {
    if (n < 0) throw std::invalid_argument("Negative index");
    if (n <= 1) return n;
    unsigned long long a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        unsigned long long c = a + b;
        a = b;
        b = c;
    }
    return b;
}




void testFactorial() {
    ASSERT_EQUAL(1, factorial_recursive(0));
    ASSERT_EQUAL(120, factorial_recursive(5));
    ASSERT_THROWS(factorial_recursive(-1));
}
void testFibonacci() {
    ASSERT_EQUAL(0, fib_iterative(0));
    ASSERT_EQUAL(1, fib_iterative(1));
    ASSERT_EQUAL(55, fib_iterative(10));

    // Мемоизация: создаём кэш размером n+1, заполняем ULLONG_MAX
    std::vector<unsigned long long> cache(41, ULLONG_MAX); // индексы 0..40
    ASSERT_EQUAL(102334155, fib_memo(40, cache));          // fib(40) = 102334155
}

void testInorderIterative() {
    BST<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    std::vector<int> rec, it;
    tree.inorder(rec);
    tree.inorder_iterative(it);
    ASSERT_TRUE(rec == it);
}
