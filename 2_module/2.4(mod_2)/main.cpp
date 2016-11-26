#include <cstdio>
#include <utility>
#include <functional>

typedef int data_t;

struct number{
    data_t value;
    size_t pos;
};

bool less(const number &lhs, const number &rhs) {
    return lhs.value < rhs.value;
}

class heap{
    size_t size;
    number * h;
    size_t cur_index;
    size_t cur_size;
public:
    heap(size_t n = 0){
        size = n;
        h = new number[n];
        cur_index = 0;
        cur_size = 0;
    }

    void heap_insert(data_t x)
    {
        if(cur_size == size)
            cur_size--;
        h[cur_size].value = x;
        h[cur_size].pos = cur_index++;
        for (size_t i = cur_size; i > 0;) {
            if (less(h[i/2], h[i])) {
                std::swap(h[i], h[i/2]);
                i = i/2;
            } else break;
        }
        cur_size++;
    }

    void heap_pop() {
        std::swap(h[--cur_size], h[0]);
        for (int i = 0; 2 * i < cur_size;) {
            i *= 2;
            if (i + 1 < cur_size && less(h[i], h[i + 1])) {
                i++;
            }
            if (less(h[i/2], h[i])) {
                std::swap(h[i/2], h[i]);
            }
            else
                break;
        }
    }

    void heap_make(data_t * data){
        for (size_t i = 0; i < size; i++) {
            heap_insert(data[i]);
        }
    }

    data_t get_top(){
        return h[0].value;
    }

    bool out_of_range(){
        return cur_size != 0 && h[0].pos <= cur_index - size;
    }

    ~heap(){
        delete [] h;
    }
};

int main() {
    size_t n, k, size = 0;
    scanf("%zu", &n);
    data_t input[n];
    while (scanf("%d", &input[size]) == 1) {
        size++;
        if (size == n)
            break;
    }
    scanf("%zu", &k);
    heap my_heap(k);
    my_heap.heap_make(input);
    printf("%d ", my_heap.get_top());
    for(size_t i = k; i < size; i++){
        while (my_heap.out_of_range()) {
            my_heap.heap_pop();
        }
        my_heap.heap_insert(input[i]);
        printf("%d ", my_heap.get_top());
    }
    return 0;
}

/*
9
10 9 8 7 6 5 4 3 2
4
*/

/*
9
7 5 0 6 43 7 6 4 8
3
*/