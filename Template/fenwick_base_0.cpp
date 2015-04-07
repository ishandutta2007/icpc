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

    static int pool_size;
    static int pool[N];
};
int FenwickTree::pool_size;
int FenwickTree::pool[N];
