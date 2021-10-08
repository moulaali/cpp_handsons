#include <iostream>

int main() {
  int i = 0;
  while (true) {
      int *p = new int;
      *p = 10;
      
      if (i % 100000 == 0) {
          std::cout << "looped\n";
      }
      
      // memory leak
      // delete p;
      i++;
  }
}
