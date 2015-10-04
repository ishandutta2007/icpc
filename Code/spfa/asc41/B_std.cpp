#include <cassert>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define clr(x) memset((x), 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define mp make_pair
#define sz(a) (a).size()
#define forab(i, st, en) for(int i=(st); i<=(int)(en); i++)
#define forabd(i, st, en) for(int i=(st); i>=(int)(en); i--)
#define forn(i, n) for(int i=0; i<(int)(n); i++)
#define fornd(i, n) for(int i=(n)-1; i>=0; i--)
#define forit(it, x) for (__typeof((x).begin()) it = (x).begin(); it != (x).end(); it++)

template <class _T> inline _T sqr(const _T& x) { return x * x; }
template <class _T> inline string str(const _T& a) { ostringstream os(""); os << a; return os.str(); }

typedef double dbl;

// Constants
const dbl PI = 3.1415926535897932384626433832795;
const dbl eps = 1e-11;

// Types
typedef signed   long long ll;
typedef unsigned long long ull;

typedef vector < int > vi;
typedef pair < int, int > pii;
typedef vector < pii > vpii;

const int maxN = (int)2e5 + 10;

set <int> blocked[maxN];
int n, m, num[maxN], col[maxN], par[maxN];
vi c[maxN];
vi dep[maxN];
vi single;

int get()
{
    int res = single[sz(single) - 1];
    single.pop_back();
    return res;
}

void dfs( int v, int pr, int d = 0 )
{
    dep[d].pb(v), par[v] = pr;
    forn(i, sz(c[v]))
    {
        int x = c[v][i];
        if (x != pr)
            dfs(x, v, d + 1);
    }
}

void setCol( int v )
{
    int pr = par[v];
    int pos = 0;
    //printf("dfs(%d) [n = %d, m = %d]\n", v, n, m);
    forn(i, sz(c[v]))
    {
        int x = c[v][i];
        if (x != pr)
        {
            if (sz(single))
                col[x] = get();
            else
            {
                while (pos < m)
                {
                    //printf("pos = %d\n", pos);
                    if (!num[pos] || blocked[pos].count(col[v]))
                    {
                        //printf("%d : %d, %d\n", pos, num[pos], blocked[pos].count(col[v]));
                        pos++;
                    }
                    else
                        break;
                }
                //puts("yes");
                assert(pos < m);
                col[x] = pos, num[pos]--;
            }
            //printf("%d <-- %d\n", x, pos);
            blocked[col[x]].insert(col[v]);
            blocked[col[v]].insert(col[x]);
        }
    }
}

int main()
{
#ifdef ROOM_311
    time_t et_0 = clock();
#endif
    freopen("bicoloring.in", "rt", stdin);
    freopen("bicoloring.out", "wt", stdout);
    cout << setiosflags(ios::fixed) << setprecision(10);

    scanf("%d", &n);
    forn(i, n - 1)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        a--, b--;
        c[a].pb(b), c[b].pb(a);
    }

    vpii pairs;
    m = n / 2 + 1;
    forn(i, m)
        num[i] = 1, single.pb(i);
    reverse(all(single));
    forn(i, m)
        blocked[i].insert(i);

    dfs(0, -1);
    col[0] = get();
    forn(ii, n)
        forn(jj, sz(dep[ii]))
        setCol(dep[ii][jj]);

    forn(i, n)
        printf("%d ", col[i] + 1);

#ifdef ROOM_311
    time_t et_1 = clock();
    fprintf(stderr, "Execution time = %0.0lf ms\n", (et_1 - et_0) * 1000.0 / CLOCKS_PER_SEC);
#endif
    return 0;
}
