#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#define Max(a, b) ((FASTBUFFER = ((a) - (b)) >> 31), ((b) & FASTBUFFER | (a) & ~FASTBUFFER))
#define Min(a, b) ((FASTBUFFER = ((a) - (b)) >> 31), ((a) & FASTBUFFER | (b) & ~FASTBUFFER))
#define Swap(a, b) (a ^= b, b ^= a, a ^= b)
#define OO 2147483647
#define priority_queue PQ

using namespace std;

int FASTBUFFER;

int C[55][55];
int f[20][2][2][2][2][2][2][4];
vector <int> v[5][5];
vector <int> vn;
long long n;

void work() {
	for (int i = 1; i <= 3; i++) {
		long long a, l, r;
		v[i][0].clear();
		v[i][1].clear();
		v[i][2].clear();
		cin >> a >> l >> r;
		while (a) {
			v[i][0].push_back(a % 47);
			v[i][1].push_back(l % 47);
			v[i][2].push_back(r % 47);
			a /= 47;
			l /= 47;
			r /= 47;
		}
	}
	
	memset(f, 0, sizeof(f));
	cin >> n;
	vn.clear();
	while (n) {
		vn.push_back(n % 47);
		n /= 47;
	}
	
	for (int i = 1; i <= 3; i++) {
		for (int j = 0; j <= 2; j++) {
			while (v[i][j].size() < vn.size()) {
				v[i][j].push_back(0);
			}
		}
	}
	
	int ans = 0;
	f[0][1][1][1][1][1][1][0] = 1; 
	for (int i = 0; i <= (int)vn.size(); i++) {
		int bit = (int)vn.size() - i - 1;
		for (int al = 0; al <= 1; al++) {
			for (int ar = 0; ar <= 1; ar++) {
				for (int bl = 0; bl <= 1; bl++) {
					for (int br = 0; br <= 1; br++) {
						for (int cl = 0; cl <= 1; cl++) {
							for (int cr = 0; cr <= 1; cr++) {
								for (int x = 0; x <= 3; x++) {
									int now = f[i][al][ar][bl][br][cl][cr][x];
									if (bit == -1) {
										(ans += now) %= 47;
										continue;
									}
									
									if (!now) {
										continue;
									}
									
									for (int a = (al ? v[1][1][bit] : 0); a <= (ar ? v[1][2][bit] : 46); a++) {
										if (a > v[1][0][bit]) {
											continue;
										}
										
										for (int b = (bl ? v[2][1][bit] : 0); b <= (br ? v[2][2][bit] : 46); b++) {
											if (b > v[2][0][bit]) {
												continue;
											}
											
											for (int c = (cl ? v[3][1][bit] : 0); c <= (cr ? v[3][2][bit] : 46); c++) {
												if (c > v[3][0][bit]) {
													continue;
												}
												
												int z = (a + b + c) / 47, newz;
												if (z < x) {
													newz = 3;
												} else if (z > x) {
													continue;
												} else {
													newz = vn[bit] - (a + b + c) % 47;
													if (newz < 0) {
														continue;
													} else if (newz > 2) {
														newz = 3;
													}
												}
												
												(f[i + 1][al && (a == v[1][1][bit])]
													[ar && (a == v[1][2][bit])]
													[bl && (b == v[2][1][bit])]
													[br && (b == v[2][2][bit])]
													[cl && (c == v[3][1][bit])]
													[cr && (c == v[3][2][bit])]
													[newz] += 
													now * C[v[1][0][bit]][a] *
													 C[v[2][0][bit]][b] * 
													 C[v[3][0][bit]][c])
													%= 47;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	printf("%d\n", ans);
}

int test;

int main() {
	C[0][0] = 1;
	for (int i = 1; i <= 50; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % 47;
		}
	}
	
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	scanf("%d", &test);
	while (test--) {
		work();
	}
	
	return 0;
}
