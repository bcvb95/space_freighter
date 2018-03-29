#include <iostream>
#include <stdlib.h>

void RandomUniqueIntegers (int n, int range_min, int range_max, int res_arr[]) {
  srand(time(NULL));
  int range_len = range_max - range_min + 1;
  if (n-1 > range_len) { 
    std::cout << "Error" << std::endl;    
    //throw IllegalArgumentException((char*) "Not enough unique integers in given range." ); 
  }
  // generate range
  int range[range_len];
  for (int i=0; i < range_len; i++) {
    range[i] = i + range_min;
  }
  int ints_remain = n;
  int rand_int;
  for (int i=0; i < n; i++) {
    if (ints_remain == 0) {
      rand_int = 0;
    }
    else {
      rand_int = rand() % ints_remain;
    }
    res_arr[i] = range[rand_int];
    // shift down greater values
    for (int j=rand_int+1; j < range_len; j++) {
      range[j-1] = range[j];
    }
    ints_remain--;
  }
}

int main () {
  int rand_ints[4];
  RandomUniqueIntegers(4, 0, 3, rand_ints);
  std::cout << "Generated:" << std::endl;
  for (int i=0; i < 4; i++) {
    std::cout << rand_ints[i] << " " << std::endl;
  }
}
