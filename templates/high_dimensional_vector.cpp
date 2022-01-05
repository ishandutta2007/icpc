template<typename T, int num_dimensions>
struct HighDimensionalVector {
  using type = std::vector<typename HighDimensionalVector<T, num_dimensions - 1>::type>;

  template<typename... Args>
  static type make(int dim, Args&&... args) {
    return type(dim, HighDimensionalVector<T, num_dimensions - 1>::make(std::forward<Args>(args)...));
  }
};

template<typename T>
struct HighDimensionalVector<T, 0> {
  using type = T;

  static type make() { return T{}; }
  static type make(T value) { return std::move(value); }
};

template<typename T, int num_dimensions>
using HDVector = HighDimensionalVector<T, num_dimensions>;

