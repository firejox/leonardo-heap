#include <iostream>
#include <vector>
#include "LeonardoHeap.hpp"

template <class Q>
void print_queue(Q& queue) {
  while (not queue.empty()) {
    std::cout << queue.top() << " ";
    queue.pop();
  }
  std::cout << "\n";
}

int main(void) {
  Leonardo::Heap<int> h;

  for(int n : {1,8,5,6,3,4,0,9,7,2})
    h.push(n);
   
  print_queue(h);

  return 0;
}
