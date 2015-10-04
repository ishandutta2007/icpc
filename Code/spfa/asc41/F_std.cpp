#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;
#define mp make_pair
#define pb push_back
#define fs first
#define sc second
#define sz(a) ((int) (a).size())
#define taskname "furniture"

const int size = 1010;

int n, m, ans;
int d[size], have[size], work[size][size], mat[size][size], rb[size], lb[size], deg[size];
bool used[size][size], was[size], bad[size];
vector <pair <int, int> > vec, h;
vector <int> vertex[size];

bool could(int day, int num)
{
	int i, j;
	h.clear();
	for (i = 0; i < day; i++)
		h.pb(mp(have[i], i));
	sort(h.rbegin(), h.rend());
	if (h.size() < m || h[m - 1].fs == 0)
	{
		bad[num] = true;
		return false;
	}
	for (i = 0; i < m; i++)
	{
		work[num][i] = h[i].sc;
		have[h[i].sc]--;
	}
	return true;
}

bool dfs(int v)
{
	if (was[v])
		return false;
	was[v] = true;
	int i;
	for (i = 0; i < vertex[v].size(); i++)
		if (rb[vertex[v][i]] == -1 || dfs(rb[vertex[v][i]]))
		{
			lb[v] = vertex[v][i];
			rb[vertex[v][i]] = v;
			return true;
		}
	return false;
}

void build_ans()
{
	int i, j, k, cnt;
	for (i = 0; i < size; i++)
		deg[i] = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			if (!bad[i])
				deg[work[i][j]]++;
	for (i = 0; i < m; i++)
	{
		//vertex[i].clear();
		for (k = 0; k < size; k++)
			vertex[k].clear();
		for (k = 0; k < n; k++)
			if (!bad[k])
			for (j = 0; j < m; j++)
				if (!used[k][work[k][j]])
					vertex[work[k][j]].pb(k);
		h.clear();
		for (k = 0; k < size; k++)
			h.pb(mp(deg[k], k));
		sort(h.rbegin(), h.rend());
		for (j = 0; j < size; j++)
		{
			rb[j] = -1;
			lb[j] = -1;
		}
		for (j = 0; j < n; j++)
			if (bad[j])
			{
				rb[j] = size + i * n + j;
				mat[j][i] = size + i * n + j;
			}
		bool flag;
		int v;
		for (j = 0; j < size; j++)
		{
			v = h[j].sc;
			if (lb[v] != -1)
				continue;
			for (k = 0; k < size; k++)
				was[k] = false;
			dfs(v);
			flag = true;
			for (k = 0; k < n; k++)
				flag = flag && (rb[k] != -1);
			if (flag)
				break;
		}
		flag = true;
		for (k = 0; k < n; k++)
			flag = flag && (rb[k] != -1);
		assert(flag);
		for (j = 0; j < size; j++)
			if (lb[j] != -1)
			{
				deg[j]--;
				used[lb[j]][j] = true;
				mat[lb[j]][i] = j;
			}
	}
}

bool try_to_place(int mid)
{
	ans = 0;
	int i;
	for (i = 0; i < size; i++)
	{
		bad[i] = false;
		have[i] = m;
	}
	for (i = 0; i < mid; i++)
		bad[vec[i].sc] = true;
	for (i = mid; i < n; i++)
		if (!could(vec[i].fs, vec[i].sc))
			return false;
	return true;
}

int main() {
	int v, i, j, lb, rb, mid;

	freopen(taskname".in", "r", stdin);
	freopen(taskname".out", "w", stdout);
	
	cin >> n >> m >> v;
	for (i = 0; i < n; i++)
	{
		cin >> d[i];
		vec.pb(mp(d[i], i));
	}
	sort(vec.begin(), vec.end());
	lb = 0;
	rb = n;
	while (lb < rb)
	{
		mid = (lb + rb) / 2;
		if (try_to_place(mid))
			rb = mid;
		else
			lb = mid + 1;
	}
	try_to_place(lb);
	ans = lb * v;
	build_ans();
	cout << ans << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			cout << mat[i][j] + 1 << ' ';
		cout << endl;
	}

	return 0;
}
