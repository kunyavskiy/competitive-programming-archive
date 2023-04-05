#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

int main() {
	string s, t;
	cin >> s >> t;
	int n = s.size(), m = t.size(), sum = 0; // n = height
	forn(i, n) sum ^= (s[i] == '1');
	forn(i, m) sum ^= (t[i] == '1');
	if (sum) {
		puts("-1");
		return 0;
	}
	char r[n][m + 1];
	forn(i, n) memset(r[i], '1', m), r[i][m] = 0;
	forn(i, m) r[0][i] = t[i] ^ ((n - 1) & 1);
	forn(i, n) r[i][0] = s[i] ^ ((m - 1) & 1);
	r[0][0] = t[0];
	for (int i = 1; i < n; i++) 
		r[0][0] ^= (r[i][0] == '1');

	int i = n - 1, j = m - 1, li = -1, lj = -1;
	while (1) {
		while (i > 0 && r[i][0] != '0') i--;
		while (j > 0 && r[0][j] != '0') j--;
		if (!i || !j)
			break;
		r[i][0] ^= 1;
		r[0][j] ^= 1;
		r[i][j] ^= 1;
		r[0][0] ^= 1;
	}
	forn(i, n) puts(r[i]);
}
