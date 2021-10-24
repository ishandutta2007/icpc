#include <bits/stdc++.h>

#pragma once

using std::to_string;
std::string to_string(const std::string& s) { return '"' + s + '"'; }
std::string to_string(const char* s) { return to_string(std::string(s)); }
std::string to_string(char c) { return std::string(1, c); }
std::string to_string(bool flag) { return flag ? "true" : "false"; }
std::string to_string(short x) { return std::to_string((int)(x)); }
std::string to_string(const std::vector<bool>& vec);
template<typename A, typename B>
std::string to_string(const std::pair<A, B>& pair);
template<typename A, typename B, typename C>
std::string to_string(const std::tuple<A, B, C>& tuple);
template<typename Container>
std::string to_string(const Container& v);
std::string debug_concat();
template<typename Head, typename... Tail>
std::string debug_concat(Head head, Tail... tail);

///////////////////// Implementation ///////////////////////

template<typename A, typename B>
std::string to_string(const std::pair<A, B>& pair) {
  return "(" + to_string(pair.first) + ", " + to_string(pair.second) + ")";
}
template<typename A, typename B, typename C>
std::string to_string(const std::tuple<A, B, C>& tuple) {
  return "(" +
    to_string(std::get<0>(tuple)) + ", " +
    to_string(std::get<1>(tuple)) + ", " +
    to_string(std::get<2>(tuple)) + ")";
}
template<typename Container>
std::string to_string(const Container& v) {
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
std::string debug_concat() { return ""; }
template<typename Head, typename... Tail>
std::string debug_concat(Head head, Tail... tail) {
  return " " + to_string(head) + debug_concat(tail...);
}

#define DUMP(...) { \
  std::stringstream ss; \
  ss << "[" << #__VA_ARGS__ << "]:" << debug_concat(__VA_ARGS__); \
  std::cerr << ss.str() << std::endl; \
}
#define CHECK(...) { \
  if (!(__VA_ARGS__)) { \
    std::cerr << "[__LINE__ " << __LINE__ << "] [" << #__VA_ARGS__ << "]: false" << std::endl; \
    exit(-1); \
  } \
}
