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

	vector<int> p(n, -1), rest, rest2;
	int size[2] = {0, 0};
	for (int i = 0; i < n; i++)
		rest.push_back(i);
	random_shuffle(rest.begin(), rest.end());
	set<int> clique;
	int cnt = 0, max_cnt = 1e7;//min(n * 1e4, 3e8);

	auto NO = [&]() {
		puts("0");
		exit(0);
	};
	function<void(int, int)> fix = [&]( int v, int dep ) {
		if (dep > 10000)
			NO();
		cnt += c[v].size();
		if (cnt > max_cnt) 
			NO();
		int deg[2] = {0, 0}, ind[2] = {-1, -1};
		for (int x : c[v])
			if (p[x] != -1)
				deg[p[x]]++, ind[p[x]] = x;
		if (deg[1] == size[1]) {
			cnt += 20;
			clique.insert(v);
			p[v] = 1, size[1]++;
		} else if (deg[0] == 0) {
			p[v] = 0, size[0]++;
		} else {
			int f0 = (deg[0] == 1), f1 = (deg[1] == size[1] - 1);
			if (!f0 && !f1)
				NO();
			if (f0 && f1)
				((rand() & 1) ? f0 : f1) = 0;
			if (f0)
				p[v] = 0, p[ind[0]] = -1, fix(ind[0], dep + 1);
			else {
				int i = -1;
				for (int x : clique)
					if (!is(v, x)) {
						i = x;
						break;
					}
				cnt += 40;
				clique.erase(i);
				clique.insert(v);
				p[v] = 1, p[i] = -1;
				fix(i, dep + 1);
			}
		}

	};
	for (int v : rest)
		fix(v, 0);
	forn(i, n)
		assert(p[i] != -1);

	vector<int> v[2], fail(n), failed(n, -1), free_move(2);
	forn(i, n)
		v[p[i]].push_back(i);
	for (int i : v[1])
		for (int j : v[1])
			if (i < j)
				assert(is(i, j));
	for (int i : v[0])
		for (int j : c[i])
			assert(p[j] == 1);
	for (int i : v[0])
		for (int j : v[1])
			if (is(i, j))
				fail[j]++, failed[j] = i;
			else
				fail[i]++, failed[i] = j;
	forn(i, n)
		free_move[p[i]] += !fail[i];
	int pairs = 0;
	forn(i, n) {
		// pairs += (failed[i] > i && failed[failed[i]] == i);
		// pairs += (failed[i] != -1 && fail[failed[i]] == 0);
		pairs += (fail[i] == 1 && failed[i] > i && fail[failed[i]] == 1 && failed[failed[i]] == i);
		pairs += (fail[i] == 1 && failed[i] != -1 && fail[failed[i]] == 0);
	}
	printf("%lld\n", ((ll)(free_move[0] + 1) * (free_move[1] + 1) + pairs) % MOD);
}
