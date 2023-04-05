#include <bits/stdc++.h>
using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int EPS = 10;
const int N = 250000 + EPS;

char s[N];
int b[N], f[N], ans[N];

void cor( int *a ) {
	forn(i, N)
		if (a[i] >= 10)
			a[i + 1] += a[i] / 10, a[i] %= 10;
}

void out( int *a ) {
  cor(a);
	int len = N - 1;
	while (len && !a[len])
		len--;
	while (len >= 0)
		printf("%d", a[len--]);
  printf("\n");
}

bool incrementBigInt(int n, char *s) {
  int i = n - 1;
  while (i >= 0 && s[i] == '9') {
    --i;
  }
  if (i < 0) { return false; }

  i = n - 1;
  while (i >= 0 && s[i] == '9') {
    s[i] = '0';
    --i;
  }
  assert(i >= 0 && s[i] < '9');
  s[i]++;
  return true;
}

int main() {
	scanf("%s", s);
	int n = strlen(s);
  n--;
	forn(j, n)
		forn(i, j)
			b[i + j]++;
	forn(L, n)
		forn(j, L)
			forn(i, j)
				f[i + j + n - L - 1]++;
	printf("n = %d\n", n);
	forn(i, 10) printf("%d ", b[i]); puts("");
	forn(i, 10) printf("%d ", f[i]); puts("");
	forn(i, N)
		ans[i] += b[i] * 36;
	forn(i, N)
		ans[i] += f[i] * 9 * 45;
  cor(ans);
  out(ans); 

  n++;
  if (incrementBigInt(n, s)) {
    for (int k = 0; k < n; ++k) {
      // printf("k %d : ", k), out(ans);
      int minD = (k == 0 ? 1 : 0);
      int maxD = s[k] - '0' - 1;
      int cntD = maxD - minD + 1;
      for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
          ans[j + n - k - 1] += (9 - (s[i] - '0')) * cntD; 
        }
        // printf("i %d\n", i);
        // out(ans); 
      }
      for (int j = 0; j < n - 1 - k; ++j) {
        ans[j + n - k - 1] += 9 * cntD - cntD * (maxD + minD) / 2;
      }
      // out(ans); 
      for (int i = 0; i < n - k - 1; ++i) {
        for (int j = 0; j < i; ++j) {
          ans[j + n - k - 2] += 45 * cntD;
        }
        // printf("i %d\n", i);
        // out(ans); 
      }
    }
  }
	out(ans); 
}
