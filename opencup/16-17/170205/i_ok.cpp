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
	int len = N - 1;
	while (len && !a[len])
		len--;
	while (len >= 0)
		printf("%d", a[len--]);
}

int main() {
	scanf("%s", s);
	int n = strlen(s);
	
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
	printf("n = %2d : ", n);
	const int M = 20;
	forn(i, M) printf("%2d ", f[i]); puts("");
	forn(i, M) printf("%2d ", f[i]); puts("");
	
	forn(i, N)
		ans[i] += b[i] * 36;
	forn(i, N)
		ans[i] += f[i] * 9 * 45;
	cor(ans);
	out(ans); 
}