#pragma once
/*
 * 17. Сжатие данных с потерями на примере ДКП (дискретного косинусного преобразования)
 *     и квантования (основа JPEG).
 *
 * Идея:
 * 1. Разбить данные (изображение) на блоки 8x8.
 * 2. Применить ДКП к каждому блоку — переход от пространственной области к частотной.
 *    Низкие частоты (верхний левый угол) наиболее важны для восприятия.
 * 3. Квантование — деление коэффициентов ДКП на матрицу квантования с округлением.
 *    Многие высокочастотные коэффициенты становятся нулями.
 * 4. Зигзагообразное сканирование и кодирование длин серий (RLE) / Хаффман — не реализовано,
 *    показан только этап ДКП + квантование + восстановление, чтобы увидеть потери.
 *
 * Сложность: O(N * M * log N) для ДКП, где N,M — размеры блока (обычно 8).
 * Для изображения размера WxH: O(W*H * 8*8*log8) ~ O(W*H).
 * Память: O(W*H).
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <locale>
using namespace std;

const double PI = 3.14159265358979323846;

// Матрица квантования JPEG (стандартная для яркости)
const int Q[8][8] = {
    {16, 11, 10, 16, 24, 40, 51, 61},
    {12, 12, 14, 19, 26, 58, 60, 55},
    {14, 13, 16, 24, 40, 57, 69, 56},
    {14, 17, 22, 29, 51, 87, 80, 62},
    {18, 22, 37, 56, 68, 109,103, 77},
    {24, 35, 55, 64, 81, 104,113, 92},
    {49, 64, 78, 87, 103,121,120,101},
    {72, 92, 95, 98, 112,100,103, 99}
};

// ДКП 2D над блоком 8x8 (вход и выход — матрица double)
void dct2D(double block[8][8]) {
    double temp[8][8] = { 0 };
    for (int u = 0; u < 8; ++u) {
        for (int v = 0; v < 8; ++v) {
            double sum = 0;
            for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                    sum += block[x][y] *
                        cos((2 * x + 1) * u * PI / (16.0)) *
                        cos((2 * y + 1) * v * PI / (16.0));
                }
            }
            double cu = (u == 0) ? (1.0 / sqrt(2)) : 1.0;
            double cv = (v == 0) ? (1.0 / sqrt(2)) : 1.0;
            temp[u][v] = 0.25 * cu * cv * sum;
        }
    }
    // копируем обратно
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            block[i][j] = temp[i][j];
}

// Обратное ДКП 2D над блоком 8x8
void idct2D(double block[8][8]) {
    double temp[8][8] = { 0 };
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            double sum = 0;
            for (int u = 0; u < 8; ++u) {
                for (int v = 0; v < 8; ++v) {
                    double cu = (u == 0) ? (1.0 / sqrt(2)) : 1.0;
                    double cv = (v == 0) ? (1.0 / sqrt(2)) : 1.0;
                    sum += cu * cv * block[u][v] *
                        cos((2 * x + 1) * u * PI / (16.0)) *
                        cos((2 * y + 1) * v * PI / (16.0));
                }
            }
            temp[x][y] = 0.25 * sum;
        }
    }
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            block[i][j] = temp[i][j];
}

// Квантование (прямое) — делим на Q и округляем
void quantize(double block[8][8]) {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            block[i][j] = round(block[i][j] / Q[i][j]);
}

// Обратное квантование — умножаем на Q
void dequantize(double block[8][8]) {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            block[i][j] *= Q[i][j];
}

void R17()
{
    setlocale(LC_ALL, "");

    // Исходный блок (пример перепада яркости)
    double original[8][8] = {
        {52, 55, 61, 66, 70, 61, 64, 73},
        {63, 59, 55, 90, 109, 85, 69, 72},
        {62, 59, 68, 113, 144, 104, 66, 73},
        {63, 58, 71, 122, 154, 106, 70, 69},
        {67, 61, 68, 104, 126, 88, 68, 70},
        {79, 65, 60, 70, 77, 68, 58, 75},
        {85, 71, 64, 59, 55, 61, 65, 83},
        {87, 79, 69, 68, 65, 76, 78, 94}
    };

    cout << "Исходный блок 8x8:\n";
    for (auto& row : original) {
        for (double val : row) cout << setw(6) << val;
        cout << "\n";
    }

    // Копируем для обработки
    double compressed[8][8];
    memcpy(compressed, original, sizeof(original));

    // Прямое ДКП
    dct2D(compressed);
    cout << "\nПосле ДКП:\n";
    for (auto& row : compressed) {
        for (double val : row) cout << setw(8) << fixed << setprecision(1) << val;
        cout << "\n";
    }

    // Квантование
    quantize(compressed);
    cout << "\nПосле квантования (многие коэффициенты стали нулями):\n";
    for (auto& row : compressed) {
        for (double val : row) cout << setw(4) << val;
        cout << "\n";
    }

    // Обратное квантование
    dequantize(compressed);
    // Обратное ДКП
    idct2D(compressed);

    cout << "\nВосстановленный блок (с потерями):\n";
    for (auto& row : compressed) {
        for (double val : row) cout << setw(6) << int(val + 0.5); // округляем для показа
        cout << "\n";
    }

    // Сравнение
    double mse = 0;
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            mse += pow(original[i][j] - compressed[i][j], 2);
    mse /= 64;
    cout << "\nСреднеквадратичная ошибка (MSE): " << mse << endl;
    cout << "Потери есть, но визуально блок похож (основные формы сохранены).\n";

}
