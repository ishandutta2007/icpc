#include <bits/stdc++.h>

#pragma once

namespace {

template<typename T>
struct has_const_iterator {
 private:
  template<typename C> static char test(typename C::const_iterator*);
  template<typename C> static int test(...);
 public:
  enum { value = sizeof(test<T>(0)) == sizeof(char) };
};

using std::to_string;
std::string to_string(const std::string& s) { return '"' + s + '"'; }
std::string to_string(const char* s) { return to_string(std::string(s)); }
std::string to_string(char c) { return std::string(1, '\'') + std::string(1, c) + "'"; }
std::string to_string(bool flag) { return flag ? "true" : "false"; }
std::string to_string(short x) { return std::to_string((int)(x)); }
std::string to_string(int8_t x) { return std::to_string((int)(x)); }
std::string to_string(const std::vector<bool>& vec);
template<typename A, typename B>
std::string to_string(const std::pair<A, B>& pair);
template<typename Tuple, size_t... Index>
std::string to_string_impl(const Tuple& tuple, std::index_sequence<Index...>);
template<typename... T>
std::string to_string(const std::tuple<T...>& tuple);
template<typename Container>
typename std::enable_if<has_const_iterator<Container>::value, std::string>::type to_string(const Container& v);
template<typename T, std::size_t N>
std::string to_string(const T(&a)[N]);
template<typename T>
std::string to_string(const T* const ptr);
std::string debug_concat();
template<typename Head, typename... Tail>
std::string debug_concat(Head&& head, Tail&&... tail);

///////////////////// Implementation ///////////////////////

template<typename A, typename B>
std::string to_string(const std::pair<A, B>& pair) {
  return "(" + to_string(pair.first) + ", " + to_string(pair.second) + ")";
}
template<typename Tuple, size_t... Index>
std::string to_string_impl(const Tuple& tuple, std::index_sequence<Index...>) {
  std::stringstream ss;
  ss << "(";
  (..., (ss << (Index == 0 ? "" : ", ") << to_string(std::get<Index>(tuple))));
  ss << ")";
  return ss.str();
}
template<typename... T>
std::string to_string(const std::tuple<T...>& tuple) {
  return to_string_impl(tuple, std::make_index_sequence<sizeof...(T)>());
}
template<typename Container>
typename std::enable_if<has_const_iterator<Container>::value, std::string>::type to_string(const Container& v) {
  bool first = true; std::string ret = "{";
  for (const auto& x : v) {
    if (first) first = false; else ret += ", "; ret += to_string(x);
  } ret += "}"; return ret;
}
std::string to_string(const std::vector<bool>& vec) {
  std::stringstream ss;
  for (int i = 0; i < vec.size(); ++i) {
    ss << (vec[i] ? 1 : 0);
  }
  return ss.str();
}
template<typename T, std::size_t N>
std::string to_string(const T(&a)[N]) {
  std::stringstream ss;
  ss << "{";
  for (int i = 0; i < N; ++i) {
    if (i) ss << ", ";
    ss << to_string(a[i]);
  }
  ss << "}";
  return ss.str();
}
template<typename T>
std::string to_string(const T* const ptr) {
  std::stringstream ss;
  ss << ptr;
  return ss.str();
}
std::string debug_concat() { return ""; }
template<typename Head, typename... Tail>
std::string debug_concat(Head&& head, Tail&&... tail) {
  return " " + to_string(std::forward<Head>(head)) + debug_concat(std::forward<Tail>(tail)...);
}

}  // namespace

#define DUMP(...) { \
  std::stringstream _D_ss; \
  _D_ss << "[" << #__VA_ARGS__ << "]:" << debug_concat(__VA_ARGS__); \
  std::cerr << _D_ss.str() << std::endl; \
}
#define CHECK(...) { \
  if (!(__VA_ARGS__)) { \
    std::cerr << "[__LINE__ " << __LINE__ << "] [" << #__VA_ARGS__ << "]: false" << std::endl; \
    exit(-1); \
  } \
}
