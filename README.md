# Leonardo Heap

Leonardo Heap was firstly introduced by Edsger W. Dijkstra in 1981 for inventing new sorting algorithm, [Smoothsort](https://en.wikipedia.org/wiki/Smoothsort). This C++ implementation is the simplified version of Smoothsort used. It can handle arbitary order insertion/delete-minimum/get-minimum operations. Furthermore, It has O(1) time get-minimum, amortized time O(1) per insertion and O(log n) per delete-minimum.

## How-to use

Here is the sample code

```cpp
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
```
## Benchmark

Here is the benchmark compare to **std::priority_queue** with the data input size 10000.

```
+----------------------+-----------------------------------+----------------------------------+
| ascending input      | per insertion (avg. comparasions) | per deletion (avg. comparasions) |
+----------------------+-----------------------------------+----------------------------------+
| std priority queue   | 11.3631                           | 11.8628                          |
+----------------------+-----------------------------------+----------------------------------+
| Leonardo Heap        | 1                                 | 4.3491                           |
+----------------------+-----------------------------------+----------------------------------+

+----------------------+-----------------------------------+----------------------------------+
| random input         | per insertion (avg. comparasions) | per deletion (avg. comparasions) |
+----------------------+-----------------------------------+----------------------------------+
| std priority queue   | 2.26928                           | 12.0134                          |
+----------------------+-----------------------------------+----------------------------------+
| Leonardo Heap        | 3.00852                           | 24.2083                          |
+----------------------+-----------------------------------+----------------------------------+

+----------------------+-----------------------------------+----------------------------------+
| descending input     | per insertion (avg. comparasions) | per deletion (avg. comparasions) |
+----------------------+-----------------------------------+----------------------------------+
| std priority queue   | 0.9999                            | 12.103                           |
+----------------------+-----------------------------------+----------------------------------+
| Leonardo Heap        | 3.5178                            | 18.4379                          |
+----------------------+-----------------------------------+----------------------------------+
```
