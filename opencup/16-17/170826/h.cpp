#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef pair<int, int> pii;
typedef long long ll;

const int N = 1 << 17;

int w, h, n, lx[N], ly[N], rx[N], ry[N], is[N][3][3], tmp[3][3];
int rev[2 * N], sum[2 * N][2];

// [vl, vr)
void build( int v, int vl, int vr ) {
	rev[v] = 0;
	sum[v][0] = vr - vl;
	sum[v][1] = 0;
	if (vr - vl == 1)
		return;
	int vm = (vl + vr) / 2;
	build(2 * v, vl, vm);
	build(2 * v + 1, vm, vr);
}

void hopahopa( int v ) {
	rev[v] ^= 1;
	swap(sum[v][0], sum[v][1]);
}

void makeRev( int v, int vl, int vr, int l, int r ) {
	if (vr <= l || r <= vl)
		return;
	if (l <= vl && vr <= r) {
		hopahopa(v);
		//printf("v=%d [%d..%d) : simple, sum = {%d, %d}, rev = %d\n", v, vl, vr, sum[v][0], sum[v][1], rev[v]);
		return;
	}
	if (rev[v]) {
		rev[v] = 0;
		hopahopa(2 * v);
		hopahopa(2 * v + 1);
	}
	int vm = (vl + vr) / 2;
	makeRev(2 * v, vl, vm, l, r);
	makeRev(2 * v + 1, vm, vr, l, r);
	forn(t, 2)
		sum[v][t] = sum[2 * v][t] + sum[2 * v + 1][t];
	//printf("v=%d [%d..%d) :       , sum = {%d, %d}, rev = %d\n", v, vl, vr, sum[v][0], sum[v][1], rev[v]);
}

// [x1, x2) [y1, y2)
vector<int> es[N];
void addRect( int x1, int x2, int y1, int y2 ) {
	if (x1 == x2 || y1 == y2) return;
	es[x1].push_back(y1);
	es[x1].push_back(y2);
	es[x2].push_back(y1);
	es[x2].push_back(y2);
}

int main() {
	scanf("%d%d%d", &w, &h, &n);
	forn(i, n) {
		scanf("%d%d%d%d", &lx[i], &ly[i], &rx[i], &ry[i]);
		lx[i]--, ly[i]--;
		is[i][1][1] = 1;
	}

	long long flips = 0;
	forn(step, 9) {
		//printf("-------> step=%d, flips=%lld\n", step,flips);
		forn(x, w + 1)
			es[x].clear();
		forn(p, n) {
			int x[] = {0, lx[p], rx[p], w};
			int y[] = {0, ly[p], ry[p], h};
			memset(tmp, 0, sizeof(tmp));
			forn(i, 3)
				forn(j, 3)
					if (is[p][i][j]) {
						//printf("p=%d i=%d j=%d\n", p, i, j);
						addRect(x[i], x[i + 1], y[j], y[j + 1]);
						int ox = (x[i + 1] - x[i]) & 1, oy = (y[j + 1] - y[j]) & 1;
						if (oy)
							forn(k, 3)
								if (k != j)
									tmp[i][k] ^= 1;
						if (ox)
							forn(k, 3)
								if (k != i)
									tmp[k][j] ^= 1;
						if (ox ^ oy)
							tmp[i][j] ^= 1;
					}
			memcpy(is[p], tmp, sizeof(tmp));
		}
		build(1, 0, h);
		long long old = flips;
		//for (auto e : es) printf("x=%d [%d..%d)\n", e.x, e.y1, e.y2);
		forn(x, w + 1) {
			sort(es[x].begin(), es[x].end());
			int i = 0, en = es[x].size();
			while (i < en) {
				if (i + 1 < en && es[x][i] == es[x][i + 1])
					i += 2; 
				else {
					makeRev(1, 0, h, es[x][i], h);
					i++;
				}
			}
			//printf("x = %d : sum = {%d, %d}\n", x, sum[1][0], sum[1][1]);
			flips += sum[1][1];
		}
		if (flips == old) {
			printf("%lld\n", old);
			return 0;
		}
	}
	puts("-1");
}
