#include <bits/stdc++.h>
using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int EPS = 10;
const int N = 2 * 250000 + EPS;

char s[N], s0[N];
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
  strcpy(s0, s);
  if (incrementBigInt(n, s)) {
    #define minD ((k == 0 ? 1 : 0))
    #define maxD (s[k] - '0' - 1)
    #define cntD (maxD - minD + 1)
    for (int k = 0; k < n; ++k) {
      for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
          ans[j + n - k - 1] += (9 - (s[i] - '0')) * cntD; 
        }
      }
    }
    for (int k = 0; k < n; ++k) {
      for (int j = 0; j < n - 1 - k; ++j) {
        ans[j + n - k - 1] += 9 * cntD - cntD * (maxD + minD) / 2;
      }
    }
    for (int k = 0; k < n; ++k) {
      for (int j = 0; j < n - k - 1; ++j) {
        for (int i = j + 1; i < n - k - 1; ++i) {
          ans[j + n - k - 2] += 45 * cntD;
        }
      }
    }
    n--;
  }
  strcpy(s, s0);

  { // calc B
    int x = n - 1;
    for (int i = 0; i <= x; i++)
      b[x - i] = b[x + i] = (n - i) / 2;
  }

  { // calc F
    int sum = 0, x = n - 2, add = 0;
    for (int i = 0; i <= x; i++) {
      f[i] = sum;
      if (i % 2 == 0) add++;
      sum += add;
    }
    for (int i = 0; i <= x; i++)
      f[x + i] = f[x - i];
  }

  forn(i, N)
    ans[i] += b[i] * 36;
  forn(i, N)
    ans[i] += f[i] * 9 * 45;

	out(ans); 
}
