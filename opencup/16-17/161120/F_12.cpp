#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int N = 1 << 20;
const int K = 2 * N;

int n, k0, k1, l[K], r[K], covered[K], value[K];
int p[N], x[N + 1], sum[N + 1];
vector<int> ind[2 * N];
int len[2 * N], used[2 * N];

struct Event { int i, type; };
queue<Event> q;

int get( int i ) {
	// assert(i <= n);
	return i == n || x[i] == -1 ? i : (p[i] = get(p[i]));
}

void go( int v, int vl, int vr, int i ) {
	if (r[i] <= vl || vr <= l[i])
		return;
	if (l[i] <= vl && vr <= r[i]) {
		ind[v].push_back(i);
		return;
	}
	int vm = (vl + vr) / 2;
	go(2 * v + 0, vl, vm, i);
	go(2 * v + 1, vm, vr, i);
}

void build( int v, int n ) {
	len[v] = n;
	if (n == 1) return;
	build(2 * v, n / 2);
	build(2 * v + 1, n / 2);
}

void make( int i ) {
	for (i += N; i > 0; i /= 2) {
		used[i]++;
		if (used[i] + 1 == len[i]) q.push(Event {i, 0});
		if (used[i] + 0 == len[i]) q.push(Event {i, 1});
	}
}

int zeroes[2 * N];
void inc( int i ) {
	for (i += N; i > 0; i /= 2)
		zeroes[i]++;
}
int get_sum( int l, int r ) {
	int res = 0;
	for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res += zeroes[l++];
		if (r & 1) res += zeroes[--r];
	}
	return res;
}

int main() {
	scanf("%d%d%d", &n, &k0, &k1);
	forn(i, k0 + k1) {
		scanf("%d%d", &l[i], &r[i]), l[i]--;
		value[i] = (i >= k0);
		go(1, 0, N, i);		
	}
	build(1, N);
	forn(i, n + 1) x[i] = -1, p[i] = i + 1;
	forn(i, N) q.push(Event {N + i, 0});
	while (q.size()) {
		Event e = q.front(); q.pop();
		int dt = e.type ? 1 : (len[e.i] - 1);
		for (int i : ind[e.i]) 
			if ((covered[i] += dt) >= r[i] - l[i] - 1) {
				covered[i] = INT_MIN;
				int pos = get(l[i]);
				if (pos < r[i]) {
					int zeroes = get_sum(l[i], r[i]);
					if ((value[i] == 0 && zeroes == 0) || (value[i] == 1 && r[i] - l[i] - 1 - zeroes == 0)) {
						x[pos] = value[i], make(pos);
						if (!x[pos])
							inc(pos);
					}
				}
			}
	}

	int cc = 0;
	forn(i, n) {
		if (x[i] == -1)
			x[i] = cc, cc ^= 1;
		sum[i + 1] = sum[i] + x[i];
	}
	forn(i, k0 + k1) {
		int len = r[i] - l[i], ones = sum[r[i]] - sum[l[i]];
		if ((value[i] && ones == 0) || (!value[i] && len - ones == 0)) {
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	forn(i, n) putchar('0' + x[i]);
	puts("");
}