#include <bits/stdc++.h>

std::string work(const std::string &s) {
    if (s.length() & 1) return s;
    std::string a = work(s.substr(0,s.length() / 2)),b = work(s.substr(s.length() / 2));
    return a < b ? a + b : b + a;
}

int main() {
    std::string sa,sb;
    std::cin >> sa >> sb;
    sa = work(sa);
    sb = work(sb);
    std::cout << (sa == sb ? "YES" : "NO") << std::endl;
}
