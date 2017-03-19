/*
1_3. Ломаная 2.
Аналогично 1.2, но ломаная должна быть замкнутая. Предполагается, что никакие три точки не лежат на одной прямой.
Указание: стройте ломаную от точки, имеющей наименьшую координату x. Если таких точек несколько, то используйте точку с наименьшей координатой y.
Точки на ломаной расположите в порядке убывания углов лучей от начальной точки до всех остальных точек.
*/

#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>

typedef int data_t;

struct Point{
    data_t x, y;
};

bool less(const data_t &lhs, const data_t &rhs) {
    return lhs < rhs;
}

bool less_angle(const Point &lhs, const Point &rhs, const Point &first) {
    if (rhs.x == first.x)
        return true;
    if (lhs.x == first.x)
        return false;
    return ((double)(lhs.y - first.y)/(lhs.x - first.x)) < (double)(rhs.y - first.y)/(rhs.x - first.x);
}

bool operator < (Point & lhs, Point & rhs) {
    return (less(lhs.x, rhs.x)) || ((!less(lhs.x, rhs.x) && !less(rhs.x, lhs.x)) && less(lhs.y, rhs.y));
}

size_t find_min(Point * arr, size_t size){
    size_t pos = 0;
    Point min = arr[0];
    for (size_t i = 1; i < size; i++) { //находим минимальную координату
        if (arr[i] < min) {
            min = arr[i];
            pos = i;
        }
    }
    return pos; //возвращаем позицию минимального
}

size_t BinarySearch(Point * arr, size_t count, Point element) { //поиск позиции для вставки элемента
    size_t first = 1;
    size_t last = count;
    while (first < last) {
        size_t mid = (first + last) / 2;
        if (less_angle(arr[mid], element, arr[0])){
            last = mid;
        }
        else
            first = mid + 1;
    }
    return first;
}

void insertion_sort(Point * arr, size_t size){
    for (size_t i = 1; i < size; i++){ //проходим по всем точкам
        Point tmp = arr[i];
        size_t pos = BinarySearch(arr, i, arr[i]); //находим, куда вставить точку
        for (size_t j = i; j > pos; --j){ //сдвигаем все остальные
            arr[j] = arr[j - 1];
        }
        arr[pos] = tmp; //ставим точку на место
    }
}

int main(){
    size_t n, i = 0;
    scanf("%zu", &n);
    Point input[n];
    while (scanf("%d %d", &input[i].x, &input[i].y) == 2) {
        i++;
        if (i == n)
            break;
    }
    n = i;
    std::swap(input[0], input[find_min(input, n)]);
    insertion_sort(input, n);
    for (i = 0; i < n; i++){
        printf("%d %d\n", input[i].x, input[i].y);
    }
    return 0;
}
