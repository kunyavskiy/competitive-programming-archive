#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef unsigned long long ll;

const int N = 100;
const int P = 239017;

int c[N][N];
ll deg[N * N];

template <const int max_size, typename HashType>
struct hashTable {
  char cc, used[max_size];
  HashType hash[max_size];
  int size;

  hashTable() { cc = 1, size = 0; }
  void clear() { cc++ ,size = 0; }

  inline int position( HashType H ) const {
    int i = H % max_size;
    while (used[i] == cc && hash[i] != H)
      if (++i == max_size)
        i = 0;
    return i;
  }

  inline bool is( HashType H ) { 
  	int pos = position(H);
  	return used[pos] == cc; 
  }
  inline void add( HashType H ) { 
  	int pos = position(H);
  	if (used[pos] != cc) {
  	  size++, used[pos] = cc, hash[pos] = H; 
  	  assert(1.3 * size <= max_size);
  	}
  }
};

const int SIZE = 1e8 + 3;
hashTable<SIZE, ll> s, s0;

int main() {
	deg[0] = 1;
	forn(i, N * N - 1)
		deg[i + 1] = deg[i] * P;
	// unordered_set<ll> s, s0;
	for (int n = 8;; n++) {
		printf("%2d: ", n);
		fflush(stdout);
		for (int size = 0; size <= 3; size++) {
			s.clear(), s0.clear();
			forn(mask, 1 << n) {
				int bn = 0;
				forn(i, n) bn += (mask >> i) & 1;
				if (bn > size)
					continue;
				vector<int> e;
				forn(i, n)
					forn(j, i)
						if (((mask >> i) & 1) || ((mask >> j) & 1))
							e.push_back(i * n + j);
				assert((int)e.size() <= 30);
				forn(p, 1 << e.size()) {
					ll E = 0;
					forn(i, e.size())
						if ((p >> i) & 1)
							E += deg[e[i]];
					(bn == size ? s : s0).add(E);
				}
			}
			int x = s.size;
			forn(i, SIZE) 
				if (s0.used[i] == s0.cc)
					x -= s.is(s0.hash[i]);
			// printf("%d,%d ", x, x & 1);
			printf("%d ", x & 1);
			fflush(stdout);
		}
		puts("");
		// printf(" --> "); 
		// int x = n * ((1 << (n - 1)) - 1 - (n - 1)) + n * (n - 1) / 2;
		// printf("%d : %d \n", x, x & 1);
	}
}