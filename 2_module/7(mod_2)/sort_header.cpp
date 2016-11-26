#include <cstdio>
#include <vector>
#include <utility>
#include <functional>
#include <stdint.h>
#include <ctime>

typedef uint32_t data_t;

class BlackInt {
public:
  explicit BlackInt(): value(0) {}
  explicit BlackInt(const uint32_t &_value): value(_value) {}
  BlackInt(BlackInt &rhs) {
    ++swap_counter;
    value = rhs.value;
  }
  explicit BlackInt(const BlackInt &rhs) {
    ++swap_counter;
    value = rhs.value;
  }

  inline bool operator == (const BlackInt &rhs) const {
    ++cmp_counter;
    return value == rhs.value;
  }
  inline bool operator != (const BlackInt &rhs) const {
    ++cmp_counter;
    return value != rhs.value;
  }
  
  inline bool operator < (const BlackInt &rhs) const {
    ++cmp_counter;
    return value < rhs.value;
  }
  inline bool operator > (const BlackInt &rhs) const {
    ++cmp_counter;
    return value > rhs.value;
  }
  inline bool operator >= (const BlackInt &rhs) const {
    ++cmp_counter;
    return value >= rhs.value;
  }
  inline bool operator <= (const BlackInt &rhs) const {
    ++cmp_counter;
    return value <= rhs.value;
  }
  
  BlackInt& operator=(const BlackInt &rhs) {
    ++swap_counter;
    value = rhs.value;
    return *this;
  }

  void swap(BlackInt &rhs) {
    ++swap_counter;
    std::swap(value, rhs.value);
  }

  static size_t get_cmp_counter() {
    return cmp_counter;
  }
  static size_t get_swap_counter() {
    return swap_counter;
  }

private:
  data_t value;
  static size_t cmp_counter;
  static size_t swap_counter; 
};

size_t BlackInt::cmp_counter = 0;
size_t BlackInt::swap_counter = 0;

namespace std {
  void swap(BlackInt &lhs, BlackInt &rhs) {
    lhs.swap(rhs);
  }
}

bool check_order(const std::vector<data_t> &data) { 
  for(size_t pos = 1; pos < data.size(); ++pos) {
    if (data[pos] < data[pos - 1]) {
      return false;
    } 
  }
  return true;
}

data_t calc_hash(const std::vector<data_t> &data) {
  data_t value = 5114;
  data_t base = 64063;
  data_t factor = 65063;
  for (size_t pos = 0; pos < data.size(); ++pos) {
    value = ((value * factor) % base + (data[pos] % base) ) % base;
  }
  return value;
}

void sort(BlackInt *begin, BlackInt *end);
int main() {
  std::vector<data_t> data;
  data_t value = 0;
  while(scanf("%u", &value) == 1) {
    data.push_back(value);
  }


  clock_t start_s = clock();  
  sort(reinterpret_cast<BlackInt*>(&data[0]), reinterpret_cast<BlackInt*>(&data[data.size()]));  
  clock_t stop_s = clock();
  size_t delta_clocks = stop_s - start_s; 
  
  printf("%d %d %zd %zd %f\n", calc_hash(data), check_order(data) ? 1 : 0, BlackInt::get_cmp_counter(), BlackInt::get_swap_counter(), delta_clocks/double(CLOCKS_PER_SEC));
  return 0;
}