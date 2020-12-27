const int kN = 1000 + 5;
const int kLog = 10 + 1;

int table[kLog][kLog][kN][kN];
int lg[kN];
int a[kN][kN];
int n, m;

int rmq(int x0, int y0, int x1, int y1) {
  int i = lg[x1 - x0 + 1];
  int j = lg[y1 - y0 + 1];
  x1 += -(1 << i) + 1;
  y1 += -(1 << j) + 1;
  return std::max({table[i][j][x0][y0], table[i][j][x0][y1], table[i][j][x1][y0], table[i][j][x1][y1]});
}

void rmqInit() {
  lg[0] = -1;
  for (int i = 1; i < kN; ++ i) {
    lg[i] = lg[i >> 1] + 1;
  }

  for (int i = 0; i <= lg[n]; ++ i) {
    for (int j = 0; j <= lg[m]; ++ j) {
      if (i + j == 0) continue;
      for (int r = 1; r + (1 << i) - 1 <= n; ++ r) {
        for (int c = 1; c + (1 << j) - 1 <= m; ++ c) {
          if (i)
            table[i][j][r][c] = std::max(table[i - 1][j][r][c], table[i - 1][j][r + (1 << i - 1)][c]);
          else
            table[i][j][r][c] = std::max(table[i][j - 1][r][c], table[i][j  - 1][r][c + (1 << j - 1)]);
        }
      }
    }
  }
}

