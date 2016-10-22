#include <bits/stdc++.h> 


struct DLX {
    static const int kMaxn = 11111;
    static const int kMaxnode = 300000+7;
    static const int kMaxr = 11111;
    int S[kMaxn];                                        // 各列节点数
    int n,sz;                                           // 列数，节点总数
    int L[kMaxnode],R[kMaxnode],U[kMaxnode],D[kMaxnode];    // 十字链表
    int ans[kMaxr],ansd;                                 // 解，解的数量
    int row[kMaxnode],col[kMaxnode];                      // 节点对应的行列编号

    void init(int num) {
        n = num;

        for (int i = 0; i <= n; i ++) {
            U[i] = i; D[i] = i; L[i] = i-1; R[i] = i+1;
        }
        L[0] = n; R[n] = 0;
        sz = n+1;
        memset(S,0,sizeof(S));
    }

    void add_row(int r,std::vector <int> line) {
        int first = sz;
        for (int i = 0; i < line.size(); i ++) {
            int c = line[i];
            L[sz] = sz-1; R[sz] = sz+1; U[sz] = U[c]; D[sz] = c;
            D[U[c]] = sz; U[c] = sz;
            row[sz] = r; col[sz] = c;
            S[c] ++; sz ++;
        }
        R[sz-1] = first; L[first] = sz-1;
    }

#define FOR(i,A,s) for (int i = A[s]; i != s; i = A[i])

    void remove(int c) {
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        FOR(i,D,c) 
            FOR(j,R,i) {
                U[D[j]] = U[j]; D[U[j]] = D[j]; S[col[j]] --;
            }
    }

    void restore(int c) {
        FOR(i,U,c)
            FOR(j,L,i) {
                U[D[j]] = j; D[U[j]] = j; S[col[j]] ++;
            }

        R[L[c]] = c;
        L[R[c]] = c;
    }

    bool dfs(int dep) {
        if (R[0]==0) {
            ansd = dep;
            return true;
        }

        int c = R[0];
        FOR(i,R,0)
            if (S[i]<S[c]) c = i;

        remove(c);
        FOR(i,D,c) {
            ans[dep] = row[i];
            FOR(j,R,i) remove(col[j]);
            if (dfs(dep+1)) return true;
            FOR(j,L,i) restore(col[j]);
        }
        restore(c);

        return false;
    }

    bool solve(std::vector <int> &v) {
        v.clear();
        if (!dfs(0)) return false;
        for (int i = 0; i < ansd; i ++) v.push_back(ans[i]);
        return true;
    }
};

int encode(int x, int y, int c)
{
    return x * 81 + y * 9 + c;
}

std::tuple<int, int, int> decode(int code)
{
    code --;
    int c = code % 9 + 1;
    int y = code / 9 % 9;
    int x = code / 81;
    return std::make_tuple(x, y, c);
}

DLX solver;
const int kN = 100;
char str[kN][kN];

int main()
{
    int answer = 0;
    static char s[32768];
    while (gets(s) != NULL) {
        for (int i = 0; i < 9; ++ i) {
            scanf("%s", str[i]);
        }
        getchar();
        solver.init(81 + 9 * 3 * 9);
        for (int i = 0; i < 9; ++ i) {
            for (int j = 0; j < 9; ++ j) {
                int b = i / 3 * 3 + j / 3;
                for (int c = 1; c <= 9; ++ c) {
                    if (str[i][j] != '0' && str[i][j] != c + '0') continue;
                    std::vector<int> vec;
                    vec.emplace_back(1 + i * 9 + j);
                    vec.emplace_back(1 + 81 + b * 9 + c - 1);
                    vec.emplace_back(1 + 81 + 81 + i * 9 + c - 1);
                    vec.emplace_back(1 + 81 + 81 + 81 + j * 9 + c - 1);
                    solver.add_row(encode(i, j, c), vec);
                }
            }
        }
        std::vector<int> cho;
        if (!solver.solve(cho)) puts("fuck");
        else {
            int result[9][9];
            for (int code : cho) {
                int i, j, c;
                std::tie(i, j, c) = decode(code);
                result[i][j] = c;
            }
            int tmp = result[0][0] * 100 + result[0][1] * 10 + result[0][2];
            printf("%d\n", tmp);
            answer += tmp;
        }
    }
    printf("answer = %d\n", answer);
}
