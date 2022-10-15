#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int n, k;
int a[11000], b[11000];

const int sz = 1100;

int res[11000][1100];
int tr[2 * sz + 10];
int tr2[2 * sz + 10];

int getmin(int *tr, int l, int r)
{
	l = max(l,0); r = max(r,0);
	l += sz;
	r += sz;
	int res = 0x7F7F7F7F;
	while (l <= r)
	{
		if (l & 1)
		{
			if (tr[l] < res) res = tr[l];
			l++;
		}
		if (!(r & 1))
		{
			if (tr[r] < res) res = tr[r];
			r--;
		}
		l >>= 1;
		r >>= 1;
	}
	return res;
}


int main()
{
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++)
		scanf("%d%d", &a[i], &b[i]);
	memset(tr, 0x7F, sizeof(tr));
	memset(tr2, 0x7F, sizeof(tr2));
	memset(res, 0x7F, sizeof(res));
	for (int j = 0; j <= k; j++)
		res[n][j] = 0;

	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = 0; j <= k; j++) {
			tr[j + sz] = res[i + 1][j];
			tr2[j + sz] = res[i + 1][j] + j;
		}
		for (int j = sz - 1; j >= 1; j--)
		{
			tr[j] = min(tr[j << 1], tr[(j << 1) ^ 1]);
			tr2[j] = min(tr2[j << 1], tr2[(j << 1) ^ 1]);
		}
		for (int j = 0; j <= k; j++) {
			if (j >= b[i]) {
				int t = res[i + 1][j - b[i]];
				if (res[i][j] > t) res[i][j] = t;
			}
			int m = b[i] - a[i] - 1;
			if (m >= 0) {
				int t = getmin(tr, j - m, j) + a[i];
				if (res[i][j] > t) res[i][j] = t;
			}
			m++;
			int m2 = min(j, b[i] - 1);
			if (m <= m2) {
				int t = getmin(tr2, j - m2, j - m) - j + b[i];
				if (res[i][j] > t) res[i][j] = t;
			}
		}
	}
	int ans = res[0][k];
	cout << ans << endl;
	return 0;
}