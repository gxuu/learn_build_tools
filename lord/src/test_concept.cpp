
#include <bits/iterator_concepts.h>
#include <stdio.h>

#include <algorithm>
#include <concepts>
#include <iostream>
#include <ranges>
#include <type_traits>
#include <vector>

template <class T>
concept IsPointer = std::is_pointer_v<T>;

template <IsPointer T>
auto min_val_p(T x, T y) {
  return *x < *y ? *x : *y;
}

// template <class T>
// requires(IsPointer<T>)
// auto min_val_p(T x, T y) -> decltype(*x) {
//   return *x < *y ? *x : *y;
// }

template <class T, class = std::enable_if_t<std::is_pointer_v<T>>>
auto min_val_p11(T x, T y) {
  printf("11\n");
  return *x < *y ? *x : *y;
}

template <class T>
concept name = requires {
  T{int{}, std::string{}};
};
template <class T>
concept has_X = requires(T t) {
  { t.X() } -> std::same_as<bool>;
};

template <has_X T>
T foo(T t) {
  return t = {114, "514"};
}

struct obj {
  int x;
  std::string y;
  obj(int x, std::string y) : x(x), y(y) {}
  bool X();
};

template <class I>
// we can put faked arguments in requires' param list
concept PseudoRandomAccessIterator = requires(I i, std::ptrdiff_t n) {
  // check whether we can perform i += n; effectively check whether operator+=(I, std::ptrdiff_t) exist
  i += n;
  // check whether we can compare ALL possible value of I with nullptr
  i == nullptr;
  // check deref i results to the same type as the return type of i.begin()
  { *i } -> std::same_as<decltype(i.begin())>;
  // the first requires is a require CLAUSE, second require is a require EXPRESSION
  requires requires(std::ptrdiff_t z) { i -= z; };
  requires requires() {
    i -= n;
    /* i -= z; results in ERROR */
  };
  // requires must be present
  // std::regular<decltype(i)> checks whether std::regular<decltype(i)> can be called
  // which is always true!
  requires std::regular<decltype(i)>;
} && std::bidirectional_iterator<I>;  // put other concepts here

template <class I>
I foobar(I i)
requires requires(I i, std::ptrdiff_t n) {
  // check whether we can perform i += n; effectively check whether operator+=(I, std::ptrdiff_t) exist
  i += n;
  // check whether we can compare ALL possible value of I with nullptr
  i == nullptr;
  // check deref i results to the same type as the return type of i.begin()
  { *i } -> std::same_as<decltype(i.begin())>;
  // the first requires is a require CLAUSE, second require is a require EXPRESSION
  requires requires(std::ptrdiff_t z) { i -= z; };
  requires requires {
    i -= n;
    /* i -= z; results in ERROR */
  };
  // requires must be present
  // std::regular<decltype(i)> checks whether std::regular<decltype(i)> can be called
  // which is always true!
  requires std::regular<decltype(i)>;
} && std::bidirectional_iterator<I>  // put other concepts here
{
  return i;
}

// todo: try if concept subsumes, try if concept together with type trait subsume

void hunos(std::integral auto x) { printf("integral\n"); }

void hunos(std::signed_integral auto x) { printf("signed integral\n"); }

int main() {
  hunos(3);
  return 0;
}
