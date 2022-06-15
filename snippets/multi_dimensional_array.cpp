template<typename T, int... DIMS> struct MultiDimensionalArrayFactory;
template<typename T, int DIM0, int... DIMS>
struct MultiDimensionalArrayFactory<T, DIM0, DIMS...> {
  using type = std::array<typename MultiDimensionalArrayFactory<T, DIMS...>::type, DIM0>;
};
template<typename T, int DIM0>
struct MultiDimensionalArrayFactory<T, DIM0> {
  using type = std::array<T, DIM0>;
};

template<typename T, int... DIMS>
using ArrayND = typename MultiDimensionalArrayFactory<T, DIMS...>::type;

