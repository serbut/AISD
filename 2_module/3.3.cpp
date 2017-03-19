/*
3_3. Закраска прямой 1.
На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка (Li и Ri). Найти длину окрашенной части числовой прямой.
*/

#include <cstdio>
#include <utility>
#include <functional>

typedef int data_t;

struct point{
    data_t value;
    bool is_begin;
    point(data_t val = NULL, bool is_b = 0){
        value = val;
        is_begin = is_b;
    }
};

void sift_down(point *input, size_t size, size_t head) {
    size_t max_ind = head;
    while (2 * head + 1 < size)
    {
        size_t child = head * 2 + 1;
        if (child < size && input[child].value > input[head].value)
            max_ind = child;
        child++;
        if (child < size && input[child].value > input[max_ind].value)
            max_ind = child;
        if (max_ind == head)
            break;
        std::swap(input[head], input[max_ind]);
        head = max_ind;
    }
}

void heap_make(point *input, size_t size) {
    size_t child = size - 1;
    while (true){
        child -= 2;
        sift_down(input, size, (child - 1) / 2);
        if (child <= 2) break;
    }
}

void sort(point * input, size_t size) {
    heap_make(input, size);
    while(size > 1) {
        size--;
        std::swap(input[0], input[size]);
        sift_down(input, size, 0);
    }
}


int main() {
    size_t n, size = 0;
    scanf("%zu", &n);
    point * input = new point[2 * n];
    data_t tmp1, tmp2;
    while (scanf("%d %d", &tmp1, &tmp2) == 2) {
        point tmp_p1(tmp1, 1);
        point tmp_p2(tmp2, 0);
        input[size++] = tmp_p1;
        input[size++] = tmp_p2;
        if (size == 2 * n)
            break;
    }
    sort(input, size);
    int layer = 0, length = 0, begin_pos = 0;
    for (int i = 0; i < size; i++){
        if(input[i].is_begin == 1){
            layer++;
            if (layer == 1)
                begin_pos = input[i].value;
        }
        else{
            layer--;
            if(layer == 0)
                length += input[i].value - begin_pos;
        }
    }
    printf("%d", length);
    return 0;
}

