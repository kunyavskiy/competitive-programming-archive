#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define sz(a) (int)(a).size()

typedef long long ll;

/** Begin fast allocation */
const int MAX_MEM = 2.4e8;
int mpos = 0;
char mem[MAX_MEM];
inline void * operator new ( size_t n ) {
	char *res = mem + mpos;
	mpos += n;
	assert(mpos <= MAX_MEM);
	return (void *)res;
}
inline void operator delete ( void * ) { }
inline void * operator new [] ( size_t ) { assert(0); }
inline void operator delete [] ( void * ) { assert(0); }
/** End fast allocation */

const int MOD = 1e9 + 7;

int main() {
	int n, m;
	scanf("%d%d", &n, &m); // <= 200 000
	int MAX = floor(sqrt(2 * m) + 1e-9); // <= 633
	vector<vector<int>> c(n);
	unordered_set<ll> all_edges(m);
	auto hash = [&]( int a, int b ) { return (ll)max(a, b) * n + min(a, b);	};
	auto is = [&]( int i, int j )   { return all_edges.count(hash(i, j)); };
	forn(_, m) {
		int a, b;
		scanf("%d%d", &a, &b), a--, b--;
		all_edges.insert(hash(a, b));
		c[a].push_back(b);
		c[b].push_back(a);
	}
	// p[0] = 0, p[1] = 1;
	// int s0 = 1, s1 = 1;
	// for (int i = 2; i < n; i++) {
	// 	int c0 = 0, c1 = 0, i0 = -1, i1 = -1;
	// 	forn(j, i) {
	// 		if (p[j]) {
	// 			if (!is(i, j)) c1++, i1 = j;
	// 		} else {
	// 			if (is(i, j))  c0++, i0 = j;
	// 		}
	// 	}
	// 	if (!c0)
	// 		p[i] = 0, s0++;
	// 	else if (!c1)
	// 		p[i] = 1, s1++;
	// 	else {
	// 		if (c1 == 1 && sz(c[i1]) <= (s1 - 1) + 1) {
	// 			int c_bad = 0, i_bad = -1;
	// 			forn(j, i)
	// 				if (p[j] == 0 && is(i1, j))
	// 					c_bad++, i_bad = j;
	// 			if (!c_bad) {
	// 				p[i1] = 0, p[i] = 1;
	// 				continue;
	// 			} 
	// 			if (c_bad == 1 && is(i_bad, i)) {
	// 				p[i1] = 0, p[i] = 1;
	// 			}
	// 		}
	// 		if (c0 == 1 && n - sz(c[i1]) - 1 <= (s0 - 1) + 1) {

	// 		}
	// 		puts("0");
	// 		return 0;
	// 	}
	// }
	vector<int> p(n, -1), rest, rest2;
	int size[2] = {1, 1};
	p[0] = 0, p[1] = 1;
	for (int i = 2; i < n; i++)
		rest.push_back(i);
	vector<int> fu(n), o;
	for (int t = 0; rest.size() && t < 1000; t++) {
		random_shuffle(rest.begin(), rest.end());
		rest2.clear();
		fill(fu.begin(), fu.end(), 0);
		for (int v : rest) {
			int deg[2] = {0, 0}, ind[2] = {-1, -1};
			for (int x : c[v])
				if (p[x] != -1)
					deg[p[x]]++, ind[p[x]] = x;
			if (deg[0] == 0) {
				p[v] = 0, size[0]++;
			} else if (deg[1] == size[1]) {
				p[v] = 1, size[1]++;
			} else {
				int ok = 0;
				if (deg[0] == 1) 
					fu[ind[0]]++, ok++;
				if (deg[1] == size[1] - 1) 
					fu[ind[1]]++, ok++;
				if (!ok) {
					puts("0");
					return 0;
				}
				rest2.push_back(v);
			}
		}
		rest.swap(rest2);
		if (rest.size()) {
			o.clear();
			forn(i, n)
				if (fu[i])
					o.push_back(i);
			sort(o.begin(), o.end(), [&]( int i, int j ){ return fu[i] > fu[j]; });
			forn(i, min(2, sz(o))) {
				int v = o[i];
				size[p[v]]--, p[v] = -1;
				rest.push_back(v);
			}
		}
	}
	if (rest.size()) {
		puts("0");
		return 0;
	}

	vector<int> v[2], fail(n), failed(n, -1), free_move(2);
	// forn(i, n)
	// 	printf("%d: %d\n", i, p[i]);
	forn(i, n)
		v[p[i]].push_back(i);
	for (int i : v[0])
		for (int j : v[1])
			if (is(i, j))
				fail[j]++, failed[j] = i;
			else
				fail[i]++, failed[i] = j;
	forn(i, n)
		free_move[p[i]] += !fail[i];
	// printf("free move = %d %d\n", free_move[0], free_move[1]);
	// forn(i, n)
	// 	printf("%d : fail = %d, i = %d\n", i, fail[i], failed[i]);
	int pairs = 0;
	forn(i, n) {
		pairs += (failed[i] > i && failed[failed[i]] == i);
		pairs += (failed[i] != -1 && fail[failed[i]] == 0);
	}
	printf("%lld\n", ((ll)(free_move[0] + 1) * (free_move[1] + 1) + pairs) % MOD);
}
