/*
7. Быстрейшая сортировка.
Дан массив данных типа BlackInt размером N < 10^10.
Требуется упорядочить его по возрастанию с использованием попарных сравнений элементов.
Решение должно содержать реализацию функции
	void sort(BlackInt *begin, BlackInt *end);
Разрешается использовать операции сравнения: < > <= >= == !=, операции присвоения между элементами типа BlackInt:
	BlackInt a = b;
	std::swap(begin[0], begin[1]);
	begin[0].swap(begin[1]);
Запрещается выполнять какие-либо операции с экземплярами класса BlackInt кроме перечисленных выше. В частности, преобразования типа или преобразование типа указателя на BlackInt.
Каждая операция сравнения стоит 1 балл.
Каждое присвоение или операция swap стоит также 1 балл.
Выигрышным объявляется решение, прошедшее тесты с минимальной стоимостью.

Пример решения, которе проходит тесты:
#include <algorithm>
void sort(BlackInt *begin, BlackInt *end) {
std::sort(begin, end);
}
Перед компиляцией к решению добавляется заголовок, организующий взаимодействие с тестовой системой.
За основу должен быть взят алгоритм быстрой сортировки.
Набор оптимизаций, который необходимо реализовать:
1. Оптимизация выбора опорного элемента.
2. Оптимизация Partition.
3. Оптимизация концевой рекурсии.
4. Написать без рекурсии.
*/

#include <iostream>
#include <stack>
#define MINSIZE 63
#define BIGSIZE 2500

struct BlackPos{
    BlackInt data;
    size_t pos;
    bool operator < (BlackPos const & rhs){
        return this->data < rhs.data;
    }
};

template <typename T>
void shells_sort(T * data, size_t size){
    for (size_t i = size/2; i > 0; i /= 2)
        for (size_t j = i; j < size; j++)
            for (size_t k = j; k >= i && data[k] < data[k - i];  k -= i)
                std::swap(data[k], data[k - i]);
}

size_t Choose_Pivot(BlackInt * data, size_t size){
    size_t middle = 0;
    if(size > BIGSIZE) {
        size_t pivot_count = 10;
        BlackPos *pivot_arr = new BlackPos[pivot_count];
        for (size_t i = 0; i < pivot_count; i++) {
            pivot_arr[i].pos = i * size/pivot_count ;
            pivot_arr[i].data = data[pivot_arr[i].pos];
        }
        shells_sort(pivot_arr, pivot_count);
        middle =  pivot_arr[pivot_count / 2].pos;
        delete [] pivot_arr;
        return middle;
    }
    middle = size / 2;
    if (data[0] < data[middle]) {
        if (data[middle] < data[size - 1]) {
            return middle;
        }
        return (data[size - 1] < data[0]) ? 0 : size - 1;
    } else {
        if (data[size - 1] < data[middle]) {
            return middle;
        }
        return (data[0] < data[size - 1]) ? size - 1 : 0;
    }
}

BlackInt * partition(BlackInt *data, size_t size) {
    size_t pivot = Choose_Pivot(data, size);
    std::swap(data[0], data[pivot]);
    pivot = 0;
    size_t i = size - 1, j = i;
    while (j > pivot)
    {
        if (data[pivot] < data[j])
        {
            std::swap(data[i], data[j]);
            i--;
        }
        j--;
    }
    std::swap(data[pivot], data[i]);
    return &data[i];
}


void sort(BlackInt *begin, BlackInt *end) {
    std::stack<std::pair<BlackInt*, BlackInt*> > stack;
    stack.push(std::make_pair(begin, end));

    while(!stack.empty()) {
        begin = stack.top().first;
        end = stack.top().second;
        stack.pop();
        if (end - begin < MINSIZE) {
            shells_sort(begin, end - begin);
            continue;
        }
        BlackInt *middle = partition(begin, end - begin), *it = middle, *jt = middle;
        while(it > begin + 1 && *it == *(it - 1))
            it--;
        while(jt < end - 1 && *jt == *(jt + 1))
            jt++;
        stack.push(std::make_pair(begin, it));
        stack.push(std::make_pair(jt + 1, end));
    }
}


