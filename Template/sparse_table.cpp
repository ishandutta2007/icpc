struct ST {
    std::vector<std::vector<int>> u;
    std::vector<int> lg;
    void build(int a[], int n) {
        std::vector<std::vector<int>>(n, std::vector<int>(20)).swap(u);
        lg.resize(n + 10);
        lg[0] = -1;
        for (int i = 1; i < lg.size(); ++ i) lg[i] = lg[i >> 1] + 1;
        for (int i = 0; i < n; ++ i) u[i][0] = a[i];
        for (int j = 1; (1 << j) <= n; ++ j) {
            for (int i = 0; i + (1 << j) <= n; ++ i) {
                u[i][j] = std::min(u[i][j- 1 ], u[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int ask(int a, int b) {
        if (a > b) std::swap(a, b);
        int k = lg[b - a + 1];
        return std::min(u[a][k], u[b - (1 << k) + 1][k]);
    }
} st;
