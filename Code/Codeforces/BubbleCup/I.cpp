#include <bits/stdc++.h>

const int N = 5000 + 1;
const int M = 100000 + 1;
int C[N][N];
int D[N + N][N];
int n,nq;
int op[M],dir[M],X[M],Y[M],len[M];
int answer[M];

void modify(int C[],int p,int dt) {
    for (int i = p; i < N; i += i & -i) {
        C[i] += dt;
    }
}

void modify2(int C[][N],int lim,int p,int l,int r) {
    for (int i = p; i < lim; i += i & -i) {
        modify(C[i],l,1);
        modify(C[i],r + 1,-1);
    }
}

int query(int C[],int p) {
    int ret = 0;
    for (int i = p; i > 0; i -= i & -i) ret += C[i];
    return ret;
}

int query2(int C[][N],int x,int y) {
    int ret = 0;
    for (int i = x; i > 0; i -= i & -i) ret += query(C[i],y);
    return ret;
}

void rotate(int &x,int &y) {
    int tx = n + 1 - y;
    int ty = x;
    x = tx;
    y = ty;
}

void get_coodinate(int x,int y,int d,int &nx,int &ny) {
    nx = x;
    ny = y;
    if (d == 1) {
        return ;
    } else if (d == 2) {
        rotate(nx,ny);
    } else if (d == 4) {
        rotate(nx,ny);
        rotate(nx,ny);
    } else {
        rotate(nx,ny);
        rotate(nx,ny);
        rotate(nx,ny);
    }
}

void work() {
    for (int d = 1; d <= 4; ++ d) {
        memset(C,0,sizeof(C));
        memset(D,0,sizeof(D));
        for (int i = 0; i < nq; ++ i) {
            if (op[i] == 1 && dir[i] != d) continue;
            int x,y;
            get_coodinate(X[i],Y[i],d,x,y);
            if (op[i] == 1) {
                modify2(C,N,x,y,y + len[i]);
                modify2(D,N + N,x + y + len[i],y,y + len[i]);
            } else {
                answer[i] += query2(C,x,y) - query2(D,x + y - 1,y);
            }
        }

    }
}

int main() {
    scanf("%d%d",&n,&nq);
    for (int i = 0; i < nq; ++ i) {
        scanf("%d",op + i);
        if (op[i] == 1) {
            scanf("%d%d%d%d",dir + i,X + i,Y + i,len + i);
        } else {
            scanf("%d%d",X + i,Y + i);
        }
    }
    work();
    for (int i = 0; i < nq; ++ i) {
        if (op[i] == 2) {
            printf("%d\n",answer[i]);
        }
    }
}
