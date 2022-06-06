template<typename T, int... DIMS>
struct MultiDimensionalArray {};

template<typename T, int DIM, int... DIMS>
struct MultiDimensionalArray<T, DIM, DIMS...> {
  using type = std::array<typename MultiDimensionalArray<T, DIMS...>::type, DIM>;

  static type create() { return type{}; }
  template<typename... Args>
  static type create(Args&&... args) {
    type ret{};
    ret.fill(MultiDimensionalArray<T, DIMS...>::create(std::forward<Args>(args)...));
    return ret;
  }
};

template<typename T, int DIM>
struct MultiDimensionalArray<T, DIM> {
  using type = std::array<T, DIM>;

  static type create() { return type{}; }
  template<typename... Args>
  static type create(Args&&... args) {
    type ret{};
    ret.fill(T(std::forward<Args>(args)...));
    return ret;
  }
};

