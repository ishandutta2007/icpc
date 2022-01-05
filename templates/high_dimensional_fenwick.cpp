template<typename T, int num_dimensions>
struct HighDimensionalFenwick {
 public:
  HighDimensionalFenwick() = default;
  virtual ~HighDimensionalFenwick() = default;

  template<typename... Args>
  explicit HighDimensionalFenwick(int dim, Args&&... args) : bits(dim, HighDimensionalFenwick<T, num_dimensions - 1>(std::forward<Args>(args)...)) {}

  template<typename... Args>
  void update(int p, Args&&... args) {
    for (int i = p; i < bits.size(); i += ~i & i + 1) bits[i].update(std::forward<Args>(args)...);
  }

  template<typename... Args>
  T query(int p, Args&&... args) const {
    T ret{};
    for (int i = p; i >= 0; i -= ~i & i + 1) ret += bits[i].query(std::forward<Args>(args)...);
    return ret;
  }

 private:
  std::vector<HighDimensionalFenwick<T, num_dimensions - 1>> bits;
};

template<typename T>
struct HighDimensionalFenwick<T, 0> {
 public:
  HighDimensionalFenwick() = default;
  virtual ~HighDimensionalFenwick() = default;
  void update(const T& dt) { val += dt; }
  T query() const { return val; }
 private:
  T val{};
};

