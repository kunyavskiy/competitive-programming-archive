#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef unsigned long long ll;

const int N = 10;

int c[N][N];

template <const int max_size, typename HashType>
struct hashTable {
  int cc, used[max_size];
  HashType hash[max_size];

  hashTable() { cc = 1; }
  void clear() { cc++; }

  inline int position( HashType H ) const {
    int i = H % max_size;
    while (used[i] == cc && hash[i] != H)
      if (++i == max_size)
        i = 0;
    return i;
  }

  inline bool is( int pos ) { return used[pos] == cc; }
  inline void add( HashType H, int pos ) { used[pos] = cc, hash[pos] = H; }
};

hashTable<(int)2e6 + 3, ll> s, s0;

int main() {
	for (int n = 1;; n++) {
		int E = n * (n - 1) / 2;
		vector<int> cnt(n + 1);
		for (int p = 0; p < (1 << E); p++) {
			int x = p;
			forn(i, n)
				forn(j, i)
					c[i][j] = x & 1, x >>= 1;
			int min_k = n;
			forn(mask, 1 << n) {
				bool good = 1;
				int bn = 0;
				forn(i, n) bn += (mask >> i) & 1;
				if (bn >= min_k)
					continue;
				forn(i, n)
					forn(j, i)
						if (c[i][j])
							if (!(((mask >> i) & 1) || ((mask >> j) & 1)))
								i = j = n, good = 0;
				if (good) 
					min_k = bn;
			}
			cnt[min_k]++;
		} 
		printf("n = %d : ", n);
		forn(i, n + 1) printf("%d ", cnt[i]); puts("");
		// printf("n = %d : ", n);
		// forn(i, n + 1) printf("%d ", cnt[i] & 1); puts("");
		printf("%d\n", n * ((1 << (n - 1)) - 1 - (n - 1)) + n * (n - 1) / 2);
	}
}