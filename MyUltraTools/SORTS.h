#pragma once
#include "Algo.h"
//11
//Формальная постановка задачи сортировки списков / массивов.
//Классификация алгоритмов сортировки по различным критериям.Прямые и
//улучшенные алгоритмы сортировки.Привести примеры прямого и
//улучшенного алгоритма сортировки, соответственно(словесно или с
//использованием схем).Показать их вычислительную сложность.


template<typename T, typename Comp = std::less<T>>
void insertionSort(std::vector<T>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        T key = arr[i];
        size_t j = i;
        while (j > 0 && Comp()(key, arr[j - 1])) {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = key;
    }
}

template<typename T, typename Comp = std::less<T>>
size_t partition(std::vector<T>& arr, size_t low, size_t high) {
    // Выбор опорного элемента: медиана из arr[low], arr[mid], arr[high]
    size_t mid = low + (high - low) / 2;
    T pivot = std::max(std::min(arr[low], arr[mid]), std::min(std::max(arr[low], arr[mid]), arr[high]));
    size_t pivotIdx;
    if (pivot == arr[low]) pivotIdx = low;
    else if (pivot == arr[mid]) pivotIdx = mid;
    else pivotIdx = high;
    std::swap(arr[pivotIdx], arr[high]); // перемещаем опорный в конец

    T pivotVal = arr[high];
    size_t i = low;
    for (size_t j = low; j < high; ++j) {
        if (Comp()(arr[j], pivotVal)) {
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }
    std::swap(arr[i], arr[high]);
    return i;
}
template<typename T, typename Comp = std::less<T>>
void quickSortRec(std::vector<T>& arr, size_t low, size_t high) {
    if (low < high) {
        size_t pi = partition<T, Comp>(arr, low, high);
        if (pi > low) quickSortRec<T, Comp>(arr, low, pi - 1); // проверка для избежания переполнения
        quickSortRec<T, Comp>(arr, pi + 1, high);
    }
}
template<typename T, typename Comp = std::less<T>>
void quickSort(std::vector<T>& arr) {
    if (!arr.empty())
        quickSortRec<T, Comp>(arr, 0, arr.size() - 1);
}



void testInsertionSort() {
    std::vector<int> arr = { 5, 2, 8, 1, 9 };
    std::vector<int> expected = arr;
    std::sort(expected.begin(), expected.end());
    insertionSort(arr);
    ASSERT_TRUE(arr == expected);
}
void testInsertionEmpty() {
    std::vector<int> arr;
    insertionSort(arr);
    ASSERT_TRUE(arr.empty());
}
void testInsertionSingle() {
    std::vector<int> arr = { 1 };
    insertionSort(arr);
    ASSERT_EQUAL(1, arr[0]);
}

void testQuickSort() {
    std::vector<int> arr = { 5, 2, 8, 1, 9 };
    std::vector<int> expected = arr;
    std::sort(expected.begin(), expected.end());
    quickSort(arr);
    ASSERT_TRUE(arr == expected);
}

void testQuickSortEmpty() {
    std::vector<int> arr;
    quickSort(arr);
    ASSERT_TRUE(arr.empty());
}
void testQuickSortSingle() {
    std::vector<int> arr = { 1 };
    quickSort(arr);
    ASSERT_EQUAL(1, arr[0]);
}
void testQuickSortLarge() {
    std::vector<int> arr;
    for (int i = 0; i < 1000; ++i) arr.push_back(rand() % 1000);
    std::vector<int> expected = arr;
    std::sort(expected.begin(), expected.end());
    quickSort(arr);
    ASSERT_TRUE(arr == expected);
}
