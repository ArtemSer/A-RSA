/*
 * Алгоритм "решето Сундарама". Выбирает все простые числа
 * до заданного (случайно сгенерированного).
*/
#include <cstring>

int sundaram(int n) {
    int *a = new int[n], i, j, k;
    memset(a, 0, sizeof(int) * n);
    for (i = 1; 3 * i + 1 < n; i++) {
        for (j = 1; (k = i + j + 2 * i * j) < n && j <= i; j++)
            a[k] = 1;
    }
//Выбирает из списка простых чисел ближайшее к заданному.

    for (i = n - 1; i >= 1; i--)
        if (a[i] == 0) {
            return (2 * i + 1);
        }
    delete[] a;
}

