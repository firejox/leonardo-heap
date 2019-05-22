#ifndef LEONARDO_HEAP_H
#define LEONARDO_HEAP_H

#include <algorithm>
#include <iterator>
#include <cstdint>

namespace Leonardo {
  int number[] = {
    1, 1, 3, 5, 9, 15, 25, 41, 67, 109, 177,
    287, 465, 753, 1219, 1973, 3193, 5167, 8361,
    13529, 21891, 35421, 57313, 92735, 150049,
    242785, 392835, 635621, 1028457, 1664079,
    2692537, 4356617, 7049155, 11405773,
    18454929, 29860703, 48315633, 78176337,
    126491971, 204668309, 331160281, 535828591,
    866988873, 1402817465
  };

  struct HeapCode {
    int64_t prefix;
    int shift;

    void increase() {
      if (3LL == (prefix & 3LL)) {
        prefix = (prefix >> 2) | 1LL;
        shift += 2;
      } else if (shift > 1) {
        prefix = (prefix << (shift - 1)) | 1LL;
        shift = 1;
      } else if (prefix) {
        prefix = (prefix << 1) | 1LL;
        shift = 0;
      } else
        prefix = 1;
    }

    void decrease() {
      if (shift > 1) {
        prefix = (prefix << 2) ^ 7LL;
        shift -= 2;
      } else
        remove_least_digit();
    }

    void remove_least_digit() {
      prefix ^= 1LL;

      if (prefix) {
        int t_shift = __builtin_ctzll(prefix);
        prefix >>= t_shift;
        shift += t_shift;
      }
    }

    void unguard_remove_least_digit() {
      int t_shift = __builtin_ctzll(prefix ^ 1);
      prefix >>= t_shift;
      shift += t_shift;
    }

  };

  template <class Iterator, class Compare>
  constexpr void heap_sift(Iterator root, int heap_size_index, Compare comp) {
    typedef typename std::iterator_traits<Iterator>::value_type value_t;

    if (heap_size_index > 1) {
      value_t value = *root;

      do {
        Iterator right_child = std::prev(root);
        Iterator left_child = std::prev(right_child, number[heap_size_index - 2]);

        if (comp(*left_child, *right_child)) {
          if (comp(value, *right_child)) {
            *root = *right_child;
            root = right_child;

            heap_size_index -= 2;
          } else break;

        } else {
          if (comp(value, *left_child)) {
            *root = *left_child;
            root = left_child;

            heap_size_index -= 1;
          } else break;
        }
      } while (heap_size_index > 1);

      *root = value;
    }
  }

  template <class Iterator, class Compare>
  constexpr void heap_trinkle(Iterator root, HeapCode code, Compare comp) {
    if (code.prefix > 1LL) {
      Iterator max_heap_root = root;
      int max_heap_size_index = code.shift;

      Iterator heap_it = root;

      do {
        std::advance(heap_it, -number[code.shift]);
        code.unguard_remove_least_digit();

        if (comp(*max_heap_root, *heap_it)) {
          max_heap_root = heap_it;
          max_heap_size_index = code.shift;
        }
      } while (code.prefix > 1LL);

      if (max_heap_root != root) {
        std::iter_swap(max_heap_root, root);
        heap_sift(max_heap_root, max_heap_size_index, comp);
      }
    }
  }

  template <class Iterator, class Compare>
  constexpr HeapCode make_heap(Iterator first, Iterator last, Compare comp) {
    HeapCode code{0LL, 1};

    if (first != last) {
      code.increase();

      for (Iterator prev_it = first, it = std::next(first); it != last; prev_it++, it++) {
        if (comp(*prev_it, *it)) {
          std::iter_swap(prev_it, it);
          heap_sift(prev_it, code.shift, comp);
        }

        code.increase();
      }
    }

    return code;
  }

  template <class Iterator, class Compare>
  constexpr HeapCode push_heap(Iterator root, HeapCode code, Compare comp) {
    Iterator prev_root = std::prev(root);

    if (comp(*root, *prev_root)) {
      std::iter_swap(root, prev_root);
      heap_sift(prev_root, code.shift, comp);
    }

    code.increase();

    return code;
  }

  template <class Iterator, class Compare>
  constexpr HeapCode pop_heap(Iterator root, HeapCode code, Compare comp) {
    code.decrease();
    heap_trinkle(std::prev(root), code, comp);
    return code;
  }

  template <class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>>
  class Heap {
    Compare comp;
    Container c;
    HeapCode code;

    public:

    typedef Container continaer_type;
    typedef Compare value_compare;
    typedef typename Container::value_type value_type;
    typedef typename Container::size_type size_type;
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;

    public:

    Heap() : Heap(Compare(), Container()) {};

    explicit Heap(const Compare& comp) : Heap(comp, Container()) {}

    Heap(const Compare& comp, const Container& cont) : comp(comp), c(cont), code(Leonardo::make_heap(std::begin(c), std::end(c), comp)) {}

    Heap(const Compare& comp, Container&& cont) : comp(comp), c(std::move(cont)), code(Leonardo::make_heap(std::begin(c), std::end(c), comp)) {}

    Heap(const Heap&) = default;

    Heap& operator=(const Heap&) = default;

    Heap(Heap&&) = default;

    Heap& operator=(Heap&&) = default;

    ~Heap() = default;

    void swap(Heap& other) noexcept(std::is_nothrow_swappable<Container>::value && std::is_nothrow_swappable<Compare>::value) {
      std::swap(c, other.c);
      std::swap(comp, other.comp);
      std::swap(code, other.code);
    }

    template <class... Args>
    void emplace(Args&&... args) {
      c.emplace_back(std::forward<Args>(args)...);
      code = Leonardo::push_heap(std::prev(std::end(c)), code, comp);
    }

    void push(const value_type& value) {
      c.push_back(value);
      code = Leonardo::push_heap(std::prev(std::end(c)), code, comp);
    }

    void push(value_type&& value) {
      c.push_back(std::move(value));
      code = Leonardo::push_heap(std::prev(std::end(c)), code, comp);
    }

    void pop() {
      code = Leonardo::pop_heap(std::prev(std::end(c)), code, comp);
      c.pop_back();
    }

    const_reference top() const { return c.back(); }
    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
  };
}


#endif
