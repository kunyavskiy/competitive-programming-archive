#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define sz(a) (int)(a).size()
#define IS(a, i) (((a) >> (i)) & 1)

typedef long long ll;

const int N = 3e5 + 10;
const int LS = -2, RS = 2;
const int LW = -2, RW = 2;

char s[N];
int n, p[N][RS - LS + 1][RW - LW + 1][4];

void make( int n, int i, int j, int last, int P ) {
	i -= 2 * n / 3;
	j -= n / 3;
	if (j > RW || i < LS) return;
	// printf("make: %d %d %d %d = %d\n", n, i, j, last, P);
	i = min(i, RS);
	j = max(j, LW);
	p[n][i - LS][j - LW][last] = P;
}

int main() {
	memset(p, -1, sizeof(p));
	scanf("%s", s);
	n = strlen(s);
	// n = 3e5;
	// forn(i, n) s[i] = '0' + (i & 1);

	forn(i, n) s[i] -= '0';
	make(0, 0, 0, 0, 0);
	make(0, 0, 1, 3, 1);
	forn(k, n - 1)
		forn(i, RS - LS + 1)
			forn(j, RW - LW + 1) 
				forn(last, 4) 
					if (p[k][i][j][last] != -1) {
						int score = 2 * k / 3 + i + LS;
						int work = k / 3 + j + LW;
						// printf("k=%d : score=%d, work=%d, last=%d\n", k, score, work ,last);
						int x = IS(last, 0) ^ s[k];
						int y = IS(last, 1) ^ s[k + 1];
						int P = (i * 10 + j) * 4 + last;
						make(k + 1, score + (x != y), work, IS(last, 1), P * 2);
						if (k + 2 < n)
							make(k + 1, score + (x != (y ^ 1)), work + 1, (IS(last, 1) ^ 1) + 2, P * 2 + 1);
					}
	int k = n - 1;
	forn(i, RS - LS + 1)
		forn(j, RW - LW + 1) 
			forn(last, 4) if (p[k][i][j][last] != -1) {
				int score = 2 * k / 3 + i + LS;
				int work = k / 3 + j + LW;
				// printf("k=%d : score=%d, work=%d, last=%d\n", k, score, work ,last);
				if (work <= n / 3 && score >= 2 * n / 3) {
					fprintf(stderr, "end is [%d,%d,%d]\n", i, j, last);
					vector<int> v;
					for (; k >= 0; k--) {
						int P = p[k][i][j][last];
						if (P % 2) v.push_back(k + 1);
						P /= 2;
						last = P % 4, P /= 4;
						j = P % 10, P /= 10;
						i = P;
					}
					printf("%d\n", sz(v));
					for (int x : v) printf("%d ", x);
					return 0;
				}
			}
	assert(0);
}
