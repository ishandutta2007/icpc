const int MOD = (int)1e9 + 7;
const int inv2 = MOD + 1 >> 1;
int A[1 << 18];

void fwt(int A[],int n,int inv) {
    for (int l = 1; l << 1 <= n; l <<= 1) {
        for (int s = 0; s < n; ++ s) {
            if (~s & l) {
                int a = A[s];
                int b = A[s ^ l];
                if (inv == 1) {
                    A[s] = (a - b + MOD) % MOD;
                    A[s ^ l] = (a + b) % MOD;
                } else {
                    A[s] = (a + b) * 1ll * inv2 % MOD;
                    A[s ^ l] = (b - a + MOD) * 1ll * inv2 % MOD;
                }
            }
        }
    }
}
