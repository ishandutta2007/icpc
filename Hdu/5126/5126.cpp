#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

const int N = 50000 + 5;

struct San : std::vector<int> {
	void prepare() {
		std::sort(begin(),end());
		erase(std::unique(begin(),end()),end());
	}
	int get(int x) {
		return std::lower_bound(begin(),end(),x)-begin();
	}
}ss;

struct Event {
	int x,y,z,slop,id;
	Event(int _x=0,int _y=0,int _z=0,int _slop=0,int _id=0)
		: x(_x), y(_y), z(_z), slop(_slop), id(_id) {}
};

struct Fenwick {
	int C[N*3];
	void modify(int p,int dt) {
		for (int i = p; i <= ss.size(); i += i&-i)
			C[i] += dt;
	}
	int query(int p) {
		int ret = 0;
		for (int i = p; i > 0; i -= i&-i)
			ret += C[i];
		return ret;
	}
}bit;

int answer[N],n,tot;
Event events[N*8];
Event events_x[N*8];
Event events_y[N*8];

bool by_x(const Event &a,const Event &b) {
	if (a.x == b.x) return a.id < b.id;
	return a.x < b.x;
}

bool by_y(const Event &a,const Event &b) {
	if (a.y == b.y) return a.id < b.id;
	return a.y < b.y;
}

void solve_y(int tot_y) {
	std::sort(events_y,events_y+tot_y,by_y);
	for (int i = 0; i < tot_y; ++ i) {
		Event &e = events_y[i];
		if (e.slop == 0)
			bit.modify(e.z,1);
		else
			answer[e.id] += e.slop * bit.query(e.z);
	}
	for (int i = 0; i < tot_y; ++ i) {
		Event &e = events_y[i];
		if (e.slop == 0)
			bit.modify(e.z,-1);
	}
}

void divide_x(int l,int r) {
	if (l >= r) return ;
	int mid = l+r>>1;
	int tot_y = 0;
	for (int i = l; i <= mid; ++ i)
		if (events_x[i].slop == 0) events_y[tot_y++] = events_x[i];
	for (int i = mid+1; i <= r; ++ i)
		if (events_x[i].slop != 0) events_y[tot_y++] = events_x[i];
	solve_y(tot_y);
	divide_x(l,mid);
	divide_x(mid+1,r);
}

void divide(int l,int r) {
	if (l >= r) return ;
	int mid = l+r>>1;
	int tot_x = 0;
	for (int i = l; i <= mid; ++ i) 
		if (events[i].slop == 0) events_x[tot_x++] = events[i];
	for (int i = mid+1; i <= r; ++ i) 
		if (events[i].slop != 0) events_x[tot_x++] = events[i];
	std::sort(events_x,events_x+tot_x,by_x);
	divide_x(0,tot_x-1);
	divide(l,mid);
	divide(mid+1,r);
}

int main() {
	int cas;
	scanf("%d",&cas);
	while (cas --) {
		scanf("%d",&n);
		ss.clear();
		tot = 0;
		for (int i = 0; i < n; ++ i) {
			int op,x0,y0,z0,x1,y1,z1;
			scanf("%d",&op);
			if (op == 1) {
				scanf("%d%d%d",&x0,&y0,&z0);
				ss.push_back(z0);
				answer[i] = -1;
				events[tot++] = Event(x0,y0,z0,0,-1);
			} else {
				scanf("%d%d%d%d%d%d",&x0,&y0,&z0,&x1,&y1,&z1);
				ss.push_back(z0);
				ss.push_back(z1);
				ss.push_back(z0-1);
				events[tot++] = Event(x1,y1,z1,1,i);
				events[tot++] = Event(x1,y0-1,z1,-1,i);
				events[tot++] = Event(x0-1,y1,z1,-1,i);
				events[tot++] = Event(x1,y1,z0-1,-1,i);
				events[tot++] = Event(x1,y0-1,z0-1,1,i);
				events[tot++] = Event(x0-1,y1,z0-1,1,i);
				events[tot++] = Event(x0-1,y0-1,z1,1,i);
				events[tot++] = Event(x0-1,y0-1,z0-1,-1,i);
				answer[i] = 0;
			}
		}
		ss.prepare();
		for (int i = 0; i < tot; ++ i) {
			events[i].z = ss.get(events[i].z) + 1;
		}
		divide(0,tot-1);
		for (int i = 0; i < n; ++ i) 
			if (answer[i] != -1)
				printf("%d\n",answer[i]);
	}	
	return 0;
}

