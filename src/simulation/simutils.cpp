#include "simutils.h"

namespace Simulation {
  void RandomUniqueIntegers (int n, int range_min, int range_max, int res_arr[]) {
    int range_len = range_max - range_min + 1;
    if (n-1 > range_len) { 
      throw IllegalArgumentException((char*) "Not enough unique integers in given range." ); 
    }
    // generate range
    int range[range_len];
    for (int i=0; i < range_len; i++) {
      range[i] = i + range_min;
    }
    int ints_remain = n;
    int rand_int;
    for (int i=0; i < n; i++) {
      rand_int = rand() % ints_remain;
      res_arr[i] = range[rand_int];
      // shift down greater values
      for (int j=rand_int+1; j < range_len; j++) {
        range[j-1] = range[j];
      }
      ints_remain--;
    }
  }

  const char* SpeciesToString (Species species) {
    switch (species) {
      case Human:
        return (char*)"Human";
      case Orcish:
        return (char*)"Orcish";
      case Elvish:
        return (char*)"Elvish";
      case Reptillian:
        return (char*)"Reptillian";
      default:
        return (char*)"Unknown";
    }
  }
}
