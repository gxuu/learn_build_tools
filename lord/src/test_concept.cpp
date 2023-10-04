
#include <stdio.h>

#include <algorithm>
#include <atomic>
#include <concepts>
#include <coroutine>
#include <iostream>
#include <map>
#include <random>
#include <ranges>
#include <set>
#include <type_traits>
#include <utility>
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

template <class T>
concept CFoo = requires(T foo) {
  { foo.func() } -> std::integral;
};

void hunos(std::integral auto) { printf("integral\n"); }

void hunos(std::signed_integral auto) { printf("signed integral\n"); }

// template <typename T>
// requires std::integral<std::remove_reference_t<decltype(*std::declval<T>())>>
template <typename T>
requires requires(T ptr) { requires std::integral<std::remove_reference_t<decltype(*ptr)>>; }
auto foobar(T ptr) {
  return *ptr;
}

// int main() {
//   int* a = new int;
//   auto res = foobar(a);
//   std::cout << res << std::endl;
//   return 0;
// }

// coroutine interface to deal with a simple task
// - providing resume() to resume the coroutine

class [[nodiscard]] CoroTask {
public:
  // initialize members for state and customization:
  struct promise_type;  // definition later in corotaskpromise.hpp
  using CoroHdl = std::coroutine_handle<promise_type>;

private:
  CoroHdl hdl;  // native coroutine handle

public:
  // constructor and destructor:
  CoroTask(auto h) : hdl{h} {  // store coroutine handle in interface
  }

  ~CoroTask() {
    if(hdl) {
      hdl.destroy();  // destroy coroutine handle
    }
  }
  // don't copy or move:
  CoroTask(const CoroTask&) = delete;
  CoroTask& operator=(const CoroTask&) = delete;

  // API to resume the coroutine
  // - returns whether there is still something to process
  bool resume() const {
    if(!hdl || hdl.done()) {
      return false;  // nothing (more) to process
    }
    hdl.resume();  // RESUME (blocks until suspended again or the end)
    return !hdl.done();
  }
};

struct CoroTask::promise_type {
  auto get_return_object() {  // init and return the coroutine interface
    return CoroTask{CoroHdl::from_promise(*this)};
  }
  auto initial_suspend() {         // initial suspend point
    return std::suspend_always{};  // - suspend immediately
  }
  void unhandled_exception() {  // deal with exceptions
    std::terminate();           // - terminate the program
  }
  void return_void() {  // deal with the end or co_return;
  }
  auto final_suspend() noexcept {  // final suspend point
    return std::suspend_always{};  // - suspend immediately
  }
};

CoroTask coro(int max) {
  std::cout << "  CORO " << max << " start" << std::endl;
  for(int val = 1; val <= max; ++val) {
    std::cout << "  CORO " << val << '/' << max << '\n';
    co_await std::suspend_always{};
  }
  std::cout << "  CORO " << max << " end" << std::endl;
}

int main() {
  namespace vws = std::views;

  // map of composers (mapping their name to their year of birth):
  std::map<std::string, int> composers{
      {"Bach",        1685},
      {"Mozart",      1756},
      {"Beethoven",   1770},
      {"Tchaikovsky", 1840},
      {"Chopin",      1810},
      {"Vivaldi ",    1678},
  };

  // iterate over the names of the first three composers born since 1700:
  for(const auto& elem : composers | vws::filter([](const auto& y) {  // since 1700
                           return y.second >= 1700;
                         }) | vws::take(3)  // first three
                             | vws::keys    // keys/names only
  ) {
    std::cout << "- " << elem << '\n';
  }

  std::vector<std::pair<int, int>> vp{
      {1, 5},
      {2, 4},
      {3, 3},
      {4, 2},
      {5, 1},
  };

  for(const auto& [k, v] : composers | std::views::take(5) | std::views::drop(2)) printf("%s, %d\n", k.c_str(), v);

  auto corotask = coro(10);
  while(corotask.resume()) {
    std::cout << "coro() suspended" << std::endl;
  }
}
