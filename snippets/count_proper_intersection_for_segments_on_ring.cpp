template<typename AngleType = long double>
struct CountProperIntersectionForSegmentsOnRing {
  int num_segments = 0;
  std::vector<std::pair<AngleType, int>> events;

  // Use angle pairs to describe a segment on ring.
  void append(const AngleType& a, const AngleType& b) {
    events.emplace_back(a, num_segments);
    events.emplace_back(b, num_segments);
    ++num_segments;
  }

  long long count() {
    long long ret = 0;
    std::sort(events.begin(), events.end());
    std::vector<int> mark(num_segments, -1);
    std::vector<int> fenwick(events.size());
    for (int i = 0, tot = 0; i < events.size(); ++i) {
      auto [angle, id] = events[i];
      if (mark[id] == -1) {
        mark[id] = i;
        for (int j = i; j < fenwick.size(); j += ~j & j + 1) ++fenwick[j];
        ++tot;
      } else {
        --tot;
        for (int j = mark[id]; j < fenwick.size(); j += ~j & j + 1) --fenwick[j];
        ret += tot;
        for (int j = mark[id]; j >= 0; j -= ~j & j + 1) ret -= fenwick[j];
        mark[id] = -1;
      }
    }
    return ret;
  }
};

