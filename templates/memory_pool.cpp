template<typename T>
class MemoryPool {
 public:
  template<typename... Args>
  T* allocate(Args&&... args) {
    if (__builtin_expect(head == nullptr, false)) {
      char* arr = new char[kReAllocBytes];
      for (int i = 0; i < kBatchSize; ++i) {
        BufferList* p = reinterpret_cast<BufferList*>(arr);
        p->next = head;
        head = p;
        arr += kUnitBytes;
      }
    }

    T* ret = reinterpret_cast<T*>(head);
    head = head->next;
    return new(ret) T(std::forward<Args>(args)...);
  }

  void free(T* ptr) {
    BufferList* p = reinterpret_cast<BufferList*>(ptr);
    p->next = head;
    head = p;
  }

 private:
  struct BufferList {
    BufferList* next = nullptr;
  };

  static constexpr int kUnitBytes = std::max(sizeof(T), sizeof(BufferList));
  static constexpr int kBatchSize = 1024;
  static constexpr int kReAllocBytes = kUnitBytes * kBatchSize;

  BufferList* head = nullptr;
};

