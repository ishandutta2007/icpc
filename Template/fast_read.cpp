template<typename T>
inline void getInt(T &x) {
    char c; bool sign = false;
    for (c = getchar(); c < '0' || c > '9'; c = getchar()) if (c == '-') sign = true;
    for (x = 0; c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - '0';
    sign && (x=-x);
}
