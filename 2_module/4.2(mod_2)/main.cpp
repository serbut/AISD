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