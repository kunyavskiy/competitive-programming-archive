#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

typedef pair<int, int> pii;

vector<pii> candidates( ll r ) {
	vector<pii> ans;
	ll m = 0;
	while ((m + 1) * (m + 1) <= r)
		m++;
	ll x = m;
	for (ll y = 0; y <= m; y++) {
		while (x * x + y * y > r)
			x--;
		if (x * x + y * y == r)
			ans.push_back({x, y});
	}
	return ans;
}

const int M = 1e6;

int n, rest = 15000;

int get() {
	int x;
	scanf("%d", &x);
	return x;
}
void out( int x, int y, ll r ) {
	assert(rest > 0);
	rest--;
	printf("? %d %d %lld\n", x, y, r);
	fflush(stdout);
}

int query( int x, int y, ll r ) {
	if (r < 0)
		return 0;
	out(x, y, r);
	return get();
}

set<pii> s;

void check( int x, int y ) {
	if (abs(x) > M || abs(y) > M)
		return;
	out(x, y, 0);
	if (get() > 0)
		s.insert(pii(x, y));
}

unsigned R() { return (rand() << 15) ^ rand(); }

void again() {
	int x = R() % (2 * M + 1) - M;
	int y = R() % (2 * M + 1) - M;
	ll r = 8e12;
	int rest_n = n;
	while (rest_n > 0) {
		ll l = -1;
		while (r - l > 1) {
			ll m = (l + r) / 2;
			if (query(x, y, m) < rest_n)
				l = m;
			else
				r = m;
		}
		vector<pii> to_check = candidates(r);
		for (auto p : to_check) {
			int dx = p.first, dy = p.second;
			check(x + dx, y + dy);
			check(x + dx, y - dy);
			check(x - dx, y + dy);
			check(x - dx, y - dy);
		}
		r = l - 1;
		rest_n = query(x, y, r);
	}
}

void ML() {
	const int L = 1e6;
	while (1)
		memset(new char[L], 1, L);
}

int main() {
	scanf("%d", &n);
	again();
	printf("!");
	if ((int)s.size() != n)
		ML();
	for (pii p : s)
		printf(" %d %d", p.first, p.second);
	puts("");
	fflush(stdout);
}
