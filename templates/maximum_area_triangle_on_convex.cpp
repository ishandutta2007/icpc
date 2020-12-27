// 已经被hack了...
// 详见https://arxiv.org/pdf/1705.11035.pdf

LL f() {
  auto vec = getConvex();
  int a = 0,b = 1,c = 2;
  int ba = 0,bb = 1,bc = 2;
  int m = vec.size();
  auto area = [&](int a,int b,int c) {
    return std::abs(det(vec[c] - vec[a],vec[b] - vec[a]));
  };
  while (true) {
    while (true) {
      while (area(a,b,c) <= area(a,b,(c + 1) % m)) c = (c + 1) % m;
      if (area(a,b,c) <= area(a,(b + 1) % m,c)) {
        b = (b + 1) % m;
        continue;
      } else {
        break;
      }
    }
    if (area(a,b,c) > area(ba,bb,bc)) {
      ba = a; bb = b; bc = c;
    }
    a = (a + 1) % m;
    if (a == b) b = (b + 1) % m;
    if (b == c) c = (c + 1) % m;
    if (a == 0) break;
  }
  return area(ba,bb,bc);
}
