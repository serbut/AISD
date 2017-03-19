/*
Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n. Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве. Напишите нерекурсивный алгоритм. 
Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).
Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении. Описание для случая прохода от начала массива к концу:
● Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
● Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
● Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
● Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
● Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
● В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.

4_2. ​Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
*/

#include <cstdio>
#include <utility>
#include <functional>

typedef int data_t;

bool less(const data_t & lhs, const data_t & rhs){
    return lhs < rhs;
}

size_t Choose_Pivot(data_t * data, size_t begin, size_t end){
    size_t middle = ((begin + end) / 2) - 1;
    if (less(data[begin], data[middle])) {
        if (less(data[middle], data[end - 1])) {
            return middle;
        }
        return (less(data[end - 1], data[begin])) ? begin : end - 1;
    } else {
        if (less(data[end - 1], data[middle])) {
            return middle;
        }
        return (less(data[begin], data[end - 1])) ? end - 1 : begin;
    }
}

size_t Partition(data_t * data, size_t begin, size_t end)
{
    size_t pivot = Choose_Pivot(data, begin, end);
    std::swap(data[begin], data[pivot]);
    pivot = begin;
    size_t i = end - 1, j = i;
    while (j > pivot)
    {
        if (less(data[pivot], data[j]))
        {
            std::swap(data[i], data[j]);
            i--;
        }
        j--;
    }
    std::swap(data[pivot], data[i]);
    return i;
}

size_t KStatistics(data_t * data, size_t size, size_t k)
{
    size_t begin = 0;
    size_t end = size;
    while (true) {
        size_t pos = Partition(data, begin, end);
        if (pos == k) {
            return pos;
        }
        if (pos > k) {
            end = pos;
        } else {
            begin = pos + 1;
        }
    }
}

int main()
{
    size_t n, k, i = 0;
    scanf("%zu %zu", &n, &k);
    data_t input[n];
    while (scanf("%d", &input[i]) == 1 && i < n)
        i++;
    printf("%d", input[KStatistics(input, n, k)]);
    return 0;
}