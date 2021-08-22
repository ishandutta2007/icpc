template<typename T>
class MemoryPool {
 public:
  T* allocate() {
    if (__builtin_expect(pool_.empty(), false)) {
      T* arr = new T[kReAllocSize];
      for (int i = 0; i < kReAllocSize; ++i) {
        pool_.emplace_back(arr + i);
      }
    }

    T* ret = pool_.back(); pool_.pop_back();
    return new(ret) T{};
  }

  void free(T* ptr) {
    pool_.emplace_back(ptr);
  }

 private:
  static constexpr int kReAllocSize = 1024;

  std::vector<T*> pool_;
};
