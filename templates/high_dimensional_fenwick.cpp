template<typename T>
class Fenwick {
 public:
  Fenwick() = default;
  virtual ~Fenwick() = default;

  template<typename... Args>
  explicit Fenwick(int n) : bits(n) {}

  template<typename... Args>
  explicit Fenwick(int n, Args... args) : bits(n, T(args...)) {}

  template<typename... Args>
  void update(int p, const T& val) {
    for (int i = p; i < bits.size(); i += ~i & i + 1) bits[i] += val;
  }

  template<typename... Args>
  void update(int p, Args... args) {
    for (int i = p; i < bits.size(); i += ~i & i + 1) bits[i].update(args...);
  }

  template<typename U, typename... Args>
  U query(int p) const {
    U ret{};
    for (int i = p; i >= 0; i -= ~i & i + 1) ret += bits[i];
    return ret;
  }

  template<typename U, typename... Args>
  U query(int p, Args... args) const {
    U ret{};
    for (int i = p; i >= 0; i -= ~i & i + 1) ret += bits[i].template query<U>(args...);
    return ret;
  }

 private:
  std::vector<T> bits;
};

