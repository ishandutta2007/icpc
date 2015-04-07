const int N = 100000 + 5;

struct FenwickTree {
    int *C,n;
    FenwickTree(int size = 0) {
        n = size;
        C = pool + pool_size;
        std::fill(C,C+size,0);
        pool_size += size;
    }
    void modify(int p,int val) {
        for (int i = p; i < n; i += ~i&i+1) C[i] += val;
    }
    int query(int p) {
        int ret = 0;
        for (int i = p; i >= 0; i -= ~i&i+1) ret += C[i];
        return ret;
    }
    int Kth(int K) {
        int p = -1;
        for (int i = 18; i >= 0; -- i) {
            p += 1 << i;
            if (p >= n || C[p] >= K) p -= 1 << i;
            else K -= C[p];
        }
        return p + 1;
    }

    static int pool_size;
    static int pool[N];
};
int FenwickTree::pool_size;
int FenwickTree::pool[N];
