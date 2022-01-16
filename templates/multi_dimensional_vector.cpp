template<typename T, int num_dimensions>
struct MultiDimensionalVector {
  using type = std::vector<typename MultiDimensionalVector<T, num_dimensions - 1>::type>;

  static type create() { return type(); }
  template<typename... Args>
  static type create(int dim, Args&&... args) {
    return type(dim, MultiDimensionalVector<T, num_dimensions - 1>::create(std::forward<Args>(args)...));
  }
};

template<typename T>
struct MultiDimensionalVector<T, 0> {
  using type = T;

  static type create() { return T{}; }
  static type create(T value) { return std::move(value); }
};

template<typename T, int num_dimensions>
using MDV = MultiDimensionalVector<T, num_dimensions>;

