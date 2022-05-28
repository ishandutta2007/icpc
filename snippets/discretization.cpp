template<typename T = long long>
struct Discretization {
 public:
  Discretization() = default;
  explicit Discretization(std::vector<T> input) : ss(std::move(input)) {
    make();
  }

  void append(T x) { ss.emplace_back(x); }
  void make() {
    std::sort(ss.begin(), ss.end());
    ss.erase(std::unique(ss.begin(), ss.end()), ss.end());
  }

  int get(T x) const {
    int pos = this->lower_bound(x);
    assert(pos < ss.size());
    assert(ss[pos] == x);
    return pos;
  }
  int lower_bound(T x) const {
    return std::lower_bound(ss.begin(), ss.end(), x) - ss.begin();
  }
  int upper_bound(T x) const {
    return std::upper_bound(ss.begin(), ss.end(), x) - ss.begin();
  }
  int size() const { return ss.size(); }
  const std::vector<T>& data() const { return ss; }

 private:
  std::vector<T> ss;
};

