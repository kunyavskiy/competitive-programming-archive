#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define IS(a, i) (((a) >> (i)) & 1)

typedef long long ll;
typedef pair<int, int> pii;

int d( int c ) {
	return isdigit(c) ? c - '0' : c + 10 - 'A';
}
int type( int x ) {
	int i = 7;
	while (i >= 0 && IS(x, i))
		i--;
	return i;
}

int value( int x ) {
	int c = 0;
	while (c < 8 && x % 2 == 0)
		c++, x >>= 1;
	return c;
}

void out( int x ) {
	char s[9];
	int sn = 0;
	while (!sn || x) {
		int d = x & 15;
		x >>= 4;
		s[sn++] = (d < 10 ? d + '0' : d - 10 + 'A');
	}
	while (sn--)
		putchar(s[sn]);
}

int main() {
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

	char s[9];
	vector<unsigned> a;
	while (scanf("%s", s) == 1) {
		int x = d(s[0]) * 16 + d(s[1]);
		a.push_back(x);
		// printf("%d:type=%d ", x, type(x));
	}
	// puts("");
	int n = a.size();
	vector<pii> ans;
	for (int i = 0; i < n; ) {
		int t = type(a[i]);
		// printf("i = %d : t = %d\n", i, t);
		if ((1 <= t && t <= 5) || t == 7) {
			int num = (t == 7 ? 0 : 6 - t), bad = 0;
			if (i + num <= n) {
				forn(j, num) {
					// printf("check: type of %d is %d\n", a[i + j + 1], type(a[i + j + 1]));
					bad |= type(a[i + j + 1]) != 6;
				}
				if (!bad) {
					auto get = [&]() {
						// printf("i=%d, t=%d, a[i]=%d : ", i, t, a[i]);
						int x = a[i++] & ((1 << t) - 1);
						// printf("x=%d next=%d\n", x, a[i] >> 6);
						forn(_, num)
							x = (x << 6) + (a[i++] & 63);
						return x;
					};
					// printf("type = %d, ", t);
					ans.push_back(pii(t, get()));
					// printf("%d\n", ans.back().second);
					continue;
				}
			}
		}
		ans.push_back(pii(-1, -1));
		i++;
	}

	// for (auto p : ans) printf("<%d, %d>\n", p.first, p.second);
	n = ans.size();
	for (int i = 0; i < n; )
		if (ans[i].first == -1)
			i++;
		else {
			int j = i;
			while (j < n && ans[j].first != -1)
				j++;
			if (j - i >= 3) {
				while (i < j)
					out(ans[i++].second), putchar(' ');
				putchar('\n');
			}
			i = j;
		}
}
