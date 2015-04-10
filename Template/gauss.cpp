const double eps = 1e-8;
int dcmp(double x) {
    return x > eps ? 1 : x < -eps ? -1 : 0;
}

int gauss(double A[N][N],double X[N],int equ,int var) {
    // 没有处理自由变元
    int i,j,k,col,max_r;
    for (k = 0, col = 0; k < equ && col < var; ++ k,++ col) {
        while (col < var) {
            max_r = k;
            for (i = k+1; i < equ; ++ i)
                if (dcmp(std::abs(A[i][col]) - std::abs(A[max_r][col])) > 0)
                    max_r = i;
            if (dcmp(A[max_r][col]) != 0) break;
            col ++;
        }
        if (col == var) break;
        if (k != max_r) {
            for (j = col; j < var; ++ j)
                std::swap(A[k][j], A[max_r][j]);
            std::swap(X[k], X[max_r]);
        }
        X[k] /= A[k][col];
        for (j = col+1; j < var; ++ j) A[k][j] /= A[k][col];
        A[k][col] = 1.;
        for (i = 0; i < equ; ++ i) {
            if (i == k || dcmp(A[i][col]) == 0) continue;
            X[i] -= X[k] * A[i][col];
            for (j = col+1; j < var; ++ j) A[i][j] -= A[k][j] * A[i][col];
            A[i][col] = 0;
        }
    }
    return 1;
}
