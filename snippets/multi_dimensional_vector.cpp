template<typename T, int NUM_DIMENSIONS>
struct MultiDimensionalVector {
  using type = std::vector<typename MultiDimensionalVector<T, NUM_DIMENSIONS - 1>::type>;

  static type create() { return type{}; }
  template<typename... Args>
  static type create(int dim, Args&&... args) {
    return type(dim, MultiDimensionalVector<T, NUM_DIMENSIONS - 1>::create(std::forward<Args>(args)...));
  }
};

template<typename T>
struct MultiDimensionalVector<T, 0> {
  using type = T;

  static type create() { return T{}; }
  static type create(T value) { return std::move(value); }
};

template<typename T, int NUM_DIMENSIONS>
using MDV = MultiDimensionalVector<T, NUM_DIMENSIONS>;

