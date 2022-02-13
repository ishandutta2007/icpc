struct FastReader {
 public:
  FastReader(FILE* in = stdin) : buffer(LENGTH), in(in) {}

  FastReader& operator>>(int& x) {
    x = next_int();
    return *this;
  }

  FastReader& operator>>(std::string& str) {
    str = next_string();
    return *this;
  }

 private:
  int next_char() {
    if (position == length) {
      position = 0, length = fread(&buffer[0], 1, LENGTH, in);
    }
    if (position == length) {
      eof = true;
      return -1;
    }
    return buffer[position++];
  }

  int next_uint() {
    int c = next_char(), x = 0;
    while (c <= 32) {
      c = next_char();
    }
    for (; '0' <= c && c <= '9'; c = next_char()) {
      x = x * 10 + c - '0';
    }
    return x;
  }

  int next_int() {
    int s = 1, c = next_char(), x = 0;
    while (c <= 32) {
      c = next_char();
    }
    if (c == '-') {
      s = -1, c = next_char();
    }
    for (; '0' <= c && c <= '9'; c = next_char()) {
      x = x * 10 + c - '0';
    }
    return x * s;
  }

  std::string next_string() {
    int c = next_char();
    while (c <= 32) {
      c = next_char();
    }
    std::stringstream ss;
    for (; c > 32; c = next_char()) {
      ss << char(c);
    }
    return ss.str();
  }

  static const int LENGTH = 1 << 16;

  std::vector<char> buffer;
  int position = 0, length = 0;
  bool eof = false;
  FILE* in = stdin;
};

